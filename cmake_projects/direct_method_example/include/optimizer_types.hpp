template <typename T> 
PoseSE2<T>::PoseSE2(const Sophus::SE2<T>& g_cw)
    : g_cw_(g_cw){
}

template<typename T>
PoseSE2<T>::~PoseSE2() {
    if(OptNode<T>::print_create_destruct())
        printf("~PoseSE2() %p\n", this);
}

template<typename T>
Point2<T>::Point2(PoseSE2<T>* f0, T uv0, T rho)
    : f0_(f0), uv0_(uv0), rho_(rho){
}

template<typename T>
Point2<T>::~Point2() {
    if(OptNode<T>::print_create_destruct())
        printf("~Point2d() %p\n", this);
}

template<typename T>
void Point2<T>::oplus(const Eigen::Matrix<T,-1,1>& dx){
    rho_ += dx(0,0);
    if(rho_ < 1e-8){
        //printf("small rho limit [%p], %f\n", this, rho_);
        rho_ = 1e-8;
    }
    if(rho_ > 10.f){
        //printf("large rho limit, %f\n", rho_);
        rho_ = 10.f;
    }
    return;
}

template<typename T>
ProjSE2Edge<T>::ProjSE2Edge(PoseSE2<T>* f, Point2<T>* pt, // f != f0
        T z)
    : z_(z)
{
    const PoseSE2<T>* f0 = pt->frame0();
    if(f == f0){
        printf("error. f0 can not be f\n");
        throw 1;
    }
    OptEdge<T>::nodes().push_back(f);
    OptEdge<T>::nodes().push_back(pt);

    f->addEdge(this);
    pt->addEdge(this);

    Eigen::Matrix<T, 1, 3 > ja;
    Eigen::Matrix<T, 1, 1 > jb;

    jacobians_.push_back(ja);
    jacobians_.push_back(jb);

    hessians_.push_back(ja.transpose()*ja);
    hessians_.push_back(jb.transpose()*jb);
    hessians_.push_back(ja.transpose()*jb);

    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(f, f));
    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(pt, pt));
    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(f, pt));

    jres_.push_back(Eigen::Matrix<T,3,1>());
    jres_.push_back(Eigen::Matrix<T,1,1>());
}

template<typename T>
Eigen::Matrix<T,-1,1> ProjSE2Edge<T>::error()const
{
    PoseSE2<T>* f = static_cast<PoseSE2<T>*>(OptEdge<T>::nodes().at(0));
    Point2<T>* pt = static_cast<Point2<T>*>(OptEdge<T>::nodes().at(1));

    T hx = ProjSE2Edge<T>::proj(f, pt);

    Eigen::Matrix<T,1,1> e(hx - z_); // 주의: 자코비안의 정의는 error notation에 따라 갈린다.

    return e;
}

template<typename T>
void ProjSE2Edge<T>::update()
{
    const auto e = error();

    PoseSE2<T>* f = static_cast<PoseSE2<T>*>(OptEdge<T>::nodes().at(0));
    Point2<T>* pt = static_cast<Point2<T>*>(OptEdge<T>::nodes().at(1));

    const PoseSE2<T>* f0 = pt->frame0();
    const Eigen::Matrix<T,2,1> x_c = f->g_cw() * pt->xw();

    Eigen::Matrix<T,1,2> dh_dXc;
    dh_dXc << - x_c.y() / (x_c.x()*x_c.x()),
           1.f / x_c.x();

    Eigen::Matrix<T,2,3> dXc_dxi;
    dXc_dxi << 1.f, 0.f, -x_c.y(),
            0.f, 1.f, x_c.x();

    Sophus::SE2<T> g_w0 = f0->g_cw().inverse();
    Eigen::Matrix<T,2,2> R_c0 = (f->g_cw() * g_w0 ).rotationMatrix();
    Eigen::Matrix<T, 2, 1> dX0_drho;

    T invd2 = pt->invd() * pt->invd();

    dX0_drho << - 1.f / invd2, - pt->uv0() / invd2;

    Eigen::Matrix<T, 1, 3 > ja = dh_dXc * dXc_dxi;
    Eigen::Matrix<T, 1, 1 > jb = dh_dXc * R_c0 * dX0_drho;

    jres_[0] = ja.transpose() * e;
    jres_[1] = jb.transpose() * e;

    hessians_[0] = ja.transpose() * ja;
    hessians_[1] = jb.transpose() * jb;
    hessians_[2] = ja.transpose() * jb;

    return;
}

template<typename T>
ProjDisparitySE2Edge<T>::ProjDisparitySE2Edge(T* offset, Point2<T>* pt, T z)
    : offset_(offset), z_(z)
{
    OptEdge<T>::nodes().push_back(pt);

    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(pt,pt));

    pt->addEdge(this);

    Eigen::Matrix<T, 1, 1> jac;
    jacobians_.push_back(jac);
    hessians_.push_back(jac.transpose() * jac);

    jres_.push_back(Eigen::Matrix<T, 1, 1>());
}

template<typename T>
void ProjDisparitySE2Edge<T>::update()
{
    // h(rho) = offset * rho
    // therefore, dh_drho = offset

    Eigen::Matrix<T, 1, 1> jac(*offset_);

    const auto e = error();

    hessians_[0] = jac.transpose() * jac;
    jres_[0]     = jac.transpose() * e;

    return;
}

template<typename T>
void GeneralOptMarginals<T>::marginalize_frame(OptNode<T>* frame, bool delete_edges)
{
    std::set<OptEdge<T>*> ff_edges;

    const size_t dim = frame->dim();

    const auto get_W = [frame, this](OptNode<T>* f, std::pair<OptNode<T>*,OptNode<T>*> idx)
                       {
                         return f<frame ? this->dUjk_.at(idx) : this->dUjk_.at(idx).transpose();
                       };
    const auto get_zero_hessian = [dim]()
                                  {
                                    return Eigen::Matrix<T,-1,-1>::Zero(dim,dim);
                                  };
    const auto get_f_other = [frame](std::pair<OptNode<T>*,OptNode<T>*> pair)
                             {
                               OptNode<T>* f_other = pair.first!=frame? pair.first : pair.second;
                               return f_other;
                             };

    // ff_edge 체크
    for(auto it = frame->edges().begin(); it != frame->edges().end(); it++)
    {
        OptEdge<T>* e = *it;

        if(e->type() == OptEdge<T>::F2F )
        {
            if(e->nodes().size() != 2 ) throw 1;

            for(size_t j=0; j<2; j++)
            {
                OptNode<T>* f = e->nodes().at(j);
                if(f->dim() != dim ) throw 1; // Not support yet
            }

            ff_edges.insert(e);
        }
        else if(e->type() == OptEdge<T>::P ) throw 1;
        else if(e->type() == OptEdge<T>::F2P )
        {
            printf("Error : marginalize or remove all f2p edge before marginalizing frame\n");
            printf("e = %p\n", e);
            throw 1;
        }
        else throw 1;
    }
    // 2. ff_edge+dUjk -> dUjk 헤시안 병합
    for(auto it_edge = ff_edges.begin(); it_edge != ff_edges.end(); it_edge++)
    {
        OptEdge<T>* e = *it_edge;

        const auto& hessians = e->hessians();
        const auto& h_domains = e->hessians_domain();

        for(size_t k = 0; k < hessians.size(); k++)
        {
            // Ordering domain
            std::pair<OptNode<T>*, OptNode<T>*> idx = h_domains.at(k);
            OptNode<T>* fa = idx.first;
            OptNode<T>* fb = idx.second;

            if(fa > fb){
                printf("Error : Un expected domain order\n");
                throw 1;
            }

            if(!dUjk_.count(idx))
                dUjk_[idx]=get_zero_hessian();

            dUjk_[idx] += hessians.at(k);
        }
        e->expire();
        if(delete_edges)
            delete e;
    }

    std::set<OptNode<T>*> f_reserved;
    std::set<std::pair<OptNode<T>*,OptNode<T>*> > ff_indices;
    for(auto it = dUjk_.begin(); it != dUjk_.end(); it++)
    {
        OptNode<T>* fa = it->first.first;
        OptNode<T>* fb = it->first.second;

        bool c1 = fa == frame;
        bool c2 = fb == frame;

        if(!c1 && !c2)
          continue; // 독립

        if(!c1)
          f_reserved.insert(fa);

        if(!c2)
          f_reserved.insert(fb);

        if(c1 && c2)
          continue;

        ff_indices.insert(it->first);
    }

    // 3. Schur complement : dU_jk -= W_j0 * U_mg^-1 * W_k0 ^T
    auto idx_ff = std::pair<OptNode<T>*,OptNode<T>*>(frame,frame);

    if(!dUjk_.count(idx_ff))
        dUjk_[idx_ff]=get_zero_hessian();

    const Eigen::Matrix<T,-1,-1> U_b_inv = dUjk_.at(idx_ff).inverse();

    if(!jres_.count(frame))
    {
        printf("Error. No Residual for frame\n");
        throw 1;
    }

    const Eigen::Matrix<T,-1,-1> jres_b = jres_.at(frame);

    for(auto it_jb = ff_indices.begin(); it_jb != ff_indices.end(); it_jb++)
    {
        OptNode<T>* fj = get_f_other(*it_jb);
        Eigen::Matrix<T,-1,-1> W_jb = get_W(fj, *it_jb);

        for(auto it_kb = it_jb; it_kb != ff_indices.end(); it_kb++)
        {
            OptNode<T>* fk = get_f_other(*it_kb);
            Eigen::Matrix<T,-1,-1> W_kb = get_W(fk, *it_kb);
            auto idx_jk = std::pair<OptNode<T>*,OptNode<T>*>(fj, fk);
            if(!dUjk_.count(idx_jk))
                dUjk_[idx_jk] = get_zero_hessian();
            dUjk_[idx_jk] -= W_jb * U_b_inv * W_kb.transpose();
        }

        if(!jres_.count(fj)) jres_[fj] = Eigen::Matrix<T,-1,1>::Zero(fj->dim()); //,1);

        jres_[fj] -= W_jb * U_b_inv * jres_b;
    }

    dUjk_.erase(idx_ff);
    jres_.erase(frame);

    for(auto it_jb = ff_indices.begin(); it_jb != ff_indices.end(); it_jb++)
        dUjk_.erase(*it_jb);

    return;
}

template<typename T>
void GeneralOptMarginals<T>::marginalize_point(OptNode<T>* pt, bool delete_edges)
{
    const auto get_frame
        = [](OptEdge<T>* e)-> OptNode<T>*
        {
          if(e->type() != OptEdge<T>::F2P) throw 1;
          return e->nodes().at(0);
        };

    const auto p_edge_get_vi
        = [&pt](OptEdge<T>* e)-> const Eigen::Matrix<T,-1,-1>&
        {
          if(e->type() != OptEdge<T>::P) throw 1;
          if(e->hessians_domain().at(0).first != pt) throw 1;
          return e->hessians().at(0);
        };

    const auto p_edge_get_jbres
        = [](OptEdge<T>* e) -> const Eigen::Matrix<T,-1,1>&
        {
          return e->jres().at(0);
        };

    const auto fp_edge_get_Uj
        = [&pt](OptEdge<T>* e)-> const Eigen::Matrix<T,-1,-1>&
        {
          if(e->type() != OptEdge<T>::F2P) throw 1;
          if(e->hessians_domain().at(1).first != pt) throw 1;
          if(e->hessians_domain().at(1).second != pt) throw 1;
          return e->hessians().at(0);
        };

    const auto fp_edge_get_vi
        = [&pt](OptEdge<T>* e)-> const Eigen::Matrix<T,-1,-1>&
        {
          if(e->type() != OptEdge<T>::F2P) throw 1;
          if(e->hessians_domain().at(1).first != pt) throw 1;
          if(e->hessians_domain().at(1).second != pt) throw 1;
          return e->hessians().at(1);
        };

    const auto fp_edge_get_jbres
        = [](OptEdge<T>* e) -> const Eigen::Matrix<T,-1,1>&
        {
          return e->jres().at(1);
        };

    const auto fp_edge_get_wij
        = [&pt](OptEdge<T>* e, OptNode<T>* fj)-> const Eigen::Matrix<T,-1,-1>&
        {
          if(e->hessians_domain().at(2).first != fj) throw 1;
          if(e->hessians_domain().at(2).second != pt) throw 1;
          if(e->type() != OptEdge<T>::F2P) throw 1;
          return e->hessians().at(2);
        };

    // 1) pt에서 wij 에 해당하는 F2P edge 추려내기.
    // 2) pt의 모든 edge로부터 V hessian 계산
    // w_ij vi^-1 w_kj^T, w_ij vi^ jbres 계산.
    std::set<OptEdge<T>*> fp_edges;
    Eigen::Matrix<T,-1,-1> hb(pt->dim(),pt->dim()); hb.setZero();
    Eigen::Matrix<T,-1,-1> jres_i(pt->dim(),1); jres_i.setZero();

    // update Vi, Uj
    for(auto it = pt->edges().begin(); it != pt->edges().end(); it++)
    {
        OptEdge<T>* e = *it;
        if(e->type() == OptEdge<T>::P)
        {
            hb += p_edge_get_vi(e);
            jres_i += p_edge_get_jbres(e);
            //printf("mg pt %p add p edge\n", this);
        }
        else if(e->type() == OptEdge<T>::F2P)
        {
            //printf("mg pt %p add fp edge\n", this);
            OptNode<T>* f = get_frame(e);
            std::pair<OptNode<T>*,OptNode<T>*> idx(f, f); // fj <= fk

            if(!dUjk_.count(idx))
                dUjk_[idx] = Eigen::Matrix<T,-1,-1>::Zero(f->dim(), f->dim());

            dUjk_[idx] += fp_edge_get_Uj(e);
            hb += fp_edge_get_vi(e);
            jres_i += fp_edge_get_jbres(e);
            fp_edges.insert(e);
        }
        else
            throw 1;
    }

    // Marginalize Vi to dUjk
    for(auto it_e1 = fp_edges.begin(); it_e1 != fp_edges.end(); it_e1++)
    {
        OptEdge<T>* e1 = *it_e1;
        OptNode<T>* f1 =  get_frame(e1);

        for(auto it_e2 = it_e1; it_e2 != fp_edges.end(); it_e2++)
        {
            OptEdge<T>* e2 = *it_e2;
            OptNode<T>* f2 = get_frame(e2);

            OptEdge<T> *eij, *eik;
            OptNode<T> *fj, *fk;

            if(f1 < f2){
                eij = e1; eik = e2;
                fj  = f1; fk  = f2;
            }
            else{
                eij = e2; eik = e1;
                fj  = f2; fk  = f1;
            }

            std::pair<OptNode<T>*,OptNode<T>*> idx(fj, fk); // fj <= fk

            if(!dUjk_.count(idx))
                dUjk_[idx] = Eigen::Matrix<T,-1,-1>::Zero(fj->dim(), fk->dim());

            // wij, wik 행렬
            const Eigen::Matrix<T,-1,-1>& wij = fp_edge_get_wij(eij, fj);
            const Eigen::Matrix<T,-1,-1> yij = wij * hb.inverse();
            const Eigen::Matrix<T,-1,-1>& wik = fp_edge_get_wij(eik, fk);

            dUjk_[idx] -= yij * wik.transpose();
        }
        // e_j -= Wij Vi^-11 e_i
        const Eigen::Matrix<T,-1,-1>& wi1 = fp_edge_get_wij(e1, f1);

        if(!jres_.count(f1))
          jres_[f1] = Eigen::Matrix<T,-1,1>::Zero(f1->dim());

        jres_[f1] -= wi1 * hb.inverse() * jres_i;
    }

    //for(auto it = fp_edges.begin(); it != fp_edges.end(); it++)
    //    (*it)->expire();

    std::set<OptEdge<T>*> edges = pt->edges();
    for(auto it = edges.begin(); it != edges.end(); it++)
    {
        (*it)->expire();
        if(delete_edges)
            delete *it;
    }
    return;
}


template<typename T>
PoseSE3<T>::PoseSE3(const Sophus::SE3<T>& g_cw, ExpMult exp_mult) 
    : g_cw_(g_cw), exp_mult_(exp_mult)
{}

template<typename T>
PoseSE3<T>::~PoseSE3()
{
    if(OptNode<T>::print_create_destruct())
        printf("~PoseSE3() %p\n", this);
}

template<typename T>
void Point3<T>::oplus(const Eigen::Matrix<T,-1,1>& dx)
{
    rho_ += dx(0,0);

    if(rho_ < 1e-8) {
        //printf("small rho limit [%p], %f\n", this, rho_);
        rho_ = 1e-8;
    }
    if(rho_ > 100.) {
        //printf("large rho limit, %f\n", rho_);
        rho_ = 100.;
    }

    return;
}

template<typename T>
ProjDisparitySE3Edge<T>::ProjDisparitySE3Edge(T* offset, Point3<T>* pt, T z)
    : offset_(offset), z_(z)
{
    OptEdge<T>::nodes().push_back(pt);

    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(pt,pt));

    pt->addEdge(this);

    Eigen::Matrix<T, 1, 1> jac;
    jacobians_.push_back(jac);
    hessians_.push_back(jac.transpose() * jac);

    jres_.push_back(Eigen::Matrix<T, 1, 1>());
}

template<typename T>
void ProjDisparitySE3Edge<T>::update()
{
    // h(rho) = offset * rho
    // therefore, dh_drho = offset

    Eigen::Matrix<T, 1, 1> jac(*offset_);

    const auto e = error();
    hessians_[0] = jac.transpose() * jac;
    jres_[0]     = jac.transpose() * e;

    return;
}

template<typename T>
ProjSE3Edge<T>::ProjSE3Edge(PoseSE3<T>* f, Point3<T>* pt, const Eigen::Matrix<T,2,1>& z)
    : z_(z)
{
    const PoseSE3<T>* f0 = pt->frame0();
    if(f == f0){
        printf("Error. f0 can not be f\n");
        throw 1;
    }

    OptEdge<T>::nodes().push_back(f);
    OptEdge<T>::nodes().push_back(pt);

    f->addEdge(this);
    pt->addEdge(this);

    Eigen::Matrix<T, 1, 6 > ja;
    Eigen::Matrix<T, 1, 1 > jb;

    jacobians_.push_back(ja);
    jacobians_.push_back(jb);

    hessians_.push_back(ja.transpose()*ja);
    hessians_.push_back(jb.transpose()*jb);
    hessians_.push_back(ja.transpose()*jb);

    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(f, f));
    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(pt, pt));
    hessians_domain_.push_back(std::pair<OptNode<T>*,OptNode<T>*>(f, pt));

    jres_.push_back(Eigen::Matrix<T,6,1>());
    jres_.push_back(Eigen::Matrix<T,1,1>());
}

template<typename T>
Eigen::Matrix<T,-1,1> ProjSE3Edge<T>::error() const
{
    PoseSE3<T>* f = static_cast<PoseSE3<T>*>(OptEdge<T>::nodes().at(0));
    Point3<T>* pt = static_cast<Point3<T>*>(OptEdge<T>::nodes().at(1));

    Eigen::Matrix<T,2,1> hx = ProjSE3Edge<T>::proj(f, pt);
    Eigen::Matrix<T,2,1> e(hx - z_);

    return e;
}

template<typename T>
void ProjSE3Edge<T>::update()
{
    const auto e = error();

    PoseSE3<T>* f = static_cast<PoseSE3<T>*>(OptEdge<T>::nodes().at(0));
    Point3<T>* pt = static_cast<Point3<T>*>(OptEdge<T>::nodes().at(1));

    const PoseSE3<T>* f0 = pt->frame0();
    const Eigen::Matrix<T,3,1> x_c = f->g_cw() * pt->xw();

    Eigen::Matrix<T,2,3> dh_dXc;

    {
        T iz = 1./x_c.z();
        T iz2 = iz*iz;
        dh_dXc << iz, 0., -x_c.x()*iz2,
               0., iz, -x_c.y()*iz2;
    }

    Eigen::Matrix<T,3,6> dXc_dxi;

    dXc_dxi.template block<3,3>(0,0).setIdentity();
    dXc_dxi.template block<3,3>(0,3) = -skew<T>(x_c);

    Sophus::SE3<T> g_w0 = f0->g_cw().inverse();
    Eigen::Matrix<T,3,3> R_c0 = (f->g_cw() * g_w0).rotationMatrix();
    Eigen::Matrix<T,3,1> dX0_drho;

    {
        // X0 = u/rho, v/rho, 1/rho
        // dX0_drho = -u/rho/rho , -v/rho/rho, -1/rho/rho
        const auto& n_uv0 = pt->n_uv0();
        T irho = 1./pt->invd();
        T irho2 = irho*irho;
        dX0_drho << -n_uv0.x()*irho2, -n_uv0.y()*irho2, -irho2;
    }

    Eigen::Matrix<T,2,6> ja = dh_dXc * dXc_dxi;
    Eigen::Matrix<T,2,1> jb = dh_dXc * R_c0 * dX0_drho;

    jres_[0] = ja.transpose() * e;
    jres_[1] = jb.transpose() * e;

    hessians_[0] = ja.transpose() * ja;
    hessians_[1] = jb.transpose() * jb;
    hessians_[2] = ja.transpose() * jb;

    return;
}
