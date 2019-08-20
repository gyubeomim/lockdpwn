template<typename T> int OptNode<T>::n_instance_ = 0;
template<typename T> int OptEdge<T>::n_instance_ = 0;
template<typename T> bool OptNode<T>::print_create_destruct_ = true;
template<typename T> bool OptEdge<T>::print_create_destruct_ = true;

// ~ Node는 edge를 지우지만
// ~ Edge는 node를 지우지 않는다.
template<typename T>
OptNode<T>::~OptNode<T>(){
  if(OptNode<T>::print_create_destruct())
    printf("~OptNode<T>() %p\n", this);
  auto cp_edges = edges_;
  for(auto it = cp_edges.begin(); it != cp_edges.end(); it++){
    OptEdge<T>* e = *it;
    e->expire();
    delete e;
  }
  n_instance_--;
}

template<typename T>
OptEdge<T>::~OptEdge<T>() {
  if(OptEdge<T>::print_create_destruct())
    printf("~OptEdge<T>() %p\n", this);
  n_instance_--;
}

template<typename T>
void OptNode<T>::removeEdge(OptEdge<T>* e) { edges_.erase(e); }

template<typename T>
void OptEdge<T>::classify(OptEdge<T>* edge,
                          std::set<OptEdge<T>*>& ff_edges,
                          std::set<OptEdge<T>*>& fp_edges,
                          std::set<OptEdge<T>*>& p_edges){
  switch(edge->type()){
    case OptEdge<T>::F2F:
      ff_edges.insert(edge);
      break;
    case OptEdge<T>::F2P:
      fp_edges.insert(edge);
      break;
    case OptEdge<T>::P:
      p_edges.insert(edge);
      break;
    default:
      printf("Error : unexpected case\n");
      throw 1;
      break;
  }
  return;
}

template<typename T>
struct OptimizeBAOption{
 public:
  OptimizeBAOption() : marginals(NULL), intf(NULL), n_iter(10), motion_update_ratio(1.) { }
  OptMarginals<T>* marginals;
  OptInterface<T>* intf;
  size_t n_iter;
  T motion_update_ratio;
};


template<typename T>
T optimize_ba(
    size_t point_dim,
    const std::set<OptNode<T>*>& target_frames,
    const std::set<OptNode<T>*>& target_points,
    const OptimizeBAOption<T>& option)
{
  static int count = 0;
  const T min_division = 1e-5;
  std::set<OptEdge<T>*> ff_edges, fp_edges, p_edges;

  // comment(edward): assign edge type to one of those (F2F, F2P, P)
  auto assign_domain = [&ff_edges, &fp_edges, &p_edges](const std::set<OptNode<T>*>& nodes,
                                                        std::map<OptNode<T>*, int>& ptr2index,
                                                        size_t& dim)
                       {
                         dim = 0;
                         for(auto it = nodes.begin(); it != nodes.end(); it++){
                           OptNode<T>* node = *it;
                           if(node->fixed()) continue;
                           ptr2index[node] = dim;
                           dim += node->dim();
                           for(auto it_e = node->edges().begin(); it_e != node->edges().end(); it_e++)
                             OptEdge<T>::classify(*it_e, ff_edges, fp_edges, p_edges);
                         }
                       };

  size_t n, m;
  std::map<OptNode<T>*, int> rj, ri;

  // assign_domain(nodes, ptr2index, dim)
  assign_domain(target_frames, rj, n);
  assign_domain(target_points, ri, m);

  Eigen::Matrix<T,-1,-1> Ha, jra, Hb, jrb;

  if(n>0){
    Ha = Eigen::Matrix<T,-1,-1>(n,n);
    jra = Eigen::Matrix<T,-1,-1>(n,1);
  }

  if(m>0){
    Hb = Eigen::Matrix<T,-1,-1>(m, point_dim );
    jrb = Eigen::Matrix<T,-1,-1>(m,1);
  }

  T chi2;
  for(size_t iter = 0; iter < option.n_iter; iter++)
  {
    if(n>0)
    {
      Ha.setZero();
      jra.setZero();

      // Ha + dHa, Jra += dJra Marginalization
      if(option.marginals)
      {
        const auto& dUjk = option.marginals->hessians();
        const auto& d_jres = option.marginals->jres();

        for(auto it_j = rj.begin(); it_j != rj.end(); it_j++){
          int j = it_j->second;
          OptNode<T>* fj = it_j->first;

          for(auto it_k = it_j; it_k != rj.end(); it_k++){
            int k = it_k->second;
            OptNode<T>* fk = it_k->first;

            auto idx_jk = std::pair<OptNode<T>*,OptNode<T>*>(fj,fk);

            if(!dUjk.count(idx_jk))
              continue;

            Ha.block(j, k, fj->dim(), fk->dim() ) += dUjk.at(idx_jk);
          }

          if(!d_jres.count(fj)) continue;

          jra.block(j, 0, fj->dim(), 1) += d_jres.at(fj);
        }
      }
    }

    if(m>0) {
      Hb.setZero();
      jrb.setZero();
    }

    chi2 = 0.;

    for(auto it_e = p_edges.begin(); it_e != p_edges.end(); it_e++) {
      // ex) disparity edge
      OptEdge<T>* edge = *it_e;

      edge->update();
      chi2 += edge->error().norm();

      const auto& hessians = edge->hessians();
      const auto& jres = edge->jres();

      OptNode<T>* n0 = edge->nodes().at(0); // Point
      int c0 = ri.at(n0);

      Hb.block(c0, 0, point_dim, point_dim) += hessians.at(0);
      jrb.block(c0,0, point_dim, 1) += jres.at(0);
    }

    for(auto it_e = ff_edges.begin(); it_e != ff_edges.end(); it_e++) {
      // TODO IMU, loop closure, later
      // printf("Error : No implementation yet\n");
      // throw 1;
      OptEdge<T>* edge = *it_e;

      edge->update();
      chi2 += edge->error().norm();

      const auto& hessians = edge->hessians();
      const auto& jres = edge->jres();

      OptNode<T>* n0 = edge->nodes().at(0); // Pose
      if(n0->fixed()) continue;

      int c0 = rj.at(n0);

      Ha.block(c0, c0, n0->dim(), n0->dim()) += hessians.at(0);
      jra.block(c0, 0, n0->dim(), 1)         += jres.at(0);
    }

    for(auto it_e = fp_edges.begin(); it_e != fp_edges.end(); it_e++) {
      OptEdge<T>* edge = *it_e;
      edge->update();
      chi2 += edge->error().norm();

      const auto& hessians = edge->hessians();
      const auto& jres = edge->jres();

      OptNode<T>* n0 = edge->nodes().at(0); // Pose
      OptNode<T>* n1 = edge->nodes().at(1); // Point

      if(!n0->fixed() && rj.count(n0) ){
        int c0 = rj.at(n0);
        Ha.block(c0, c0, n0->dim(), n0->dim()) += hessians.at(0);
        jra.block(c0, 0, n0->dim(), 1)         += jres.at(0);
      }

      if(!n1->fixed() && ri.count(n1) ){
        int c1 = ri.at(n1);
        Hb.block(c1, 0, point_dim, point_dim) += hessians.at(1);
        jrb.block(c1, 0, point_dim, 1)        += jres.at(1);
      }
    }

    // <<<< Ha += ja'ja, Hb += jb'jb  <<
    // >>>> W += ja'*jb >>>>>>>>>>>>>>>>
    // Only for F2P edge
    if(m>0 && n>0) {
      for(auto it_point = target_points.begin(); it_point != target_points.end(); it_point++) {
        OptNode<T>* pt = *it_point;

        if(pt->fixed()) continue;

        int i = ri.at(pt);

        for(auto it_e1 = pt->edges().begin(); it_e1 != pt->edges().end(); it_e1++)
        {
          OptEdge<T>* e1 = *it_e1;
          if(e1->type() != OptEdge<T>::F2P) continue;

          OptNode<T>* f1 = e1->nodes().at(0);
          if(!rj.count(f1)) continue; // fixed f1

          int j1 = rj.at(f1);

          for(auto it_e2 = it_e1; it_e2 != pt->edges().end(); it_e2++)
          {
            OptEdge<T>* e2 = *it_e2;
            if(e2->type() != OptEdge<T>::F2P) continue;

            OptNode<T>* f2 = e2->nodes().at(0);
            if(!rj.count(f2)) continue; // fixed f2

            int j2 = rj.at(f2);

            OptEdge<T>* eij, *eik;

            int j, k;

            if(j1 < j2) {
              eij = e1; eik = e2;
              j   = j1; k   = j2;
            }
            else {
              eij = e2; eik = e1;
              j   = j2; k   = j1;
            }

            const auto& wij = eij->hessians().at(2);
            const auto& wik = eik->hessians().at(2);

            const auto vi = Hb.block(i, 0, point_dim, point_dim);

            if(std::abs(vi.determinant()) < min_division) continue;

            // Schur Complement
            // Ha - W Hb^-1 W^T
            // 상삼각행렬만 계산한다.
            const auto yij = wij * vi.inverse();
            Ha.block( j, k, yij.rows(), wik.rows() ) -= yij * wik.transpose();
            jra.block(j, 0, yij.rows(), 1)           -= yij * jrb.block(i,0,point_dim,1);
          } // for it_e2
        } // for it_e1 = pt->edges()
      } // for it_node = target_points
    }// if

    Eigen::Matrix<T,-1,1> delpa;

    if(n > 0)
    {
      if( std::abs( Ha.determinant() ) < 1e-30) {
        // - variable frame이 1개일 경우, Ha의 marginalization 결과는 0 행렬!
        // vi = jb'jb  at ith point, "the" 1st var frame이 되기 때문. sum 사라짐
        printf("Error : The given graph is singular. ");
        printf("det(H) = %e\n",  Ha.determinant());
        throw 1;
      }

      delpa = - Ha.ldlt().solve(jra);

      if(rj.size() > 1)
        delpa *= option.motion_update_ratio;

      // 소용없었음. 멀쩡한 optimization도 경고띄움.
      //if(delpa.block(0,0,6,1).norm() > 0.5){
      //std::cout << "Warring : count=" << count << ", iter=" << iter << ", delpa=" << delpa.transpose() << std::endl;
      //throw 1;;
      //}

      for(auto it_j = rj.begin(); it_j != rj.end(); it_j++)
      {
        OptNode<T>* pose = it_j->first;
        int j = it_j->second;

        pose->oplus( delpa.block(j, 0, pose->dim(), 1) );
      }
    } // if(n > 0)

    for(auto it_i = ri.begin(); it_i != ri.end(); it_i++)
    {
      OptNode<T>* pt = it_i->first;
      int i = it_i->second;

      auto part_jrb = jrb.block(i,0,point_dim, point_dim);

      for(auto it_e = pt->edges().begin(); it_e != pt->edges().end(); it_e++)
      {
        OptEdge<T>* eij = *it_e;
        if(eij->type() != OptEdge<T>::F2P ) continue;

        OptNode<T>* fj = eij->nodes().at(0);
        if(fj->fixed()) continue;
        if(!rj.count(fj)) continue;

        int j = rj.at(fj);

        const auto& wij = eij->hessians().at(2);

        part_jrb += wij.transpose() * delpa.block(j,0, wij.rows(),1);
      }

      auto vi = Hb.block(i, 0, point_dim, point_dim);

      if(vi.determinant() < min_division) continue;

      Eigen::Matrix<T,-1,1> dx = - vi.inverse() * part_jrb;
      pt->oplus(dx);
    }

    if(option.intf)
    {
      OptInfo<T> info;
      info.iter_ = iter;    info.chi2_ = chi2;
      // comment(edward): info.error_ = false?
      info.error_ = false;  info.Ha_ = &Ha;
      info.Hb_ = &Hb;       info.ri_ = &ri;
      info.rj_ = &rj;

      info.ff_edges_ = & ff_edges;
      info.fp_edges_ = & fp_edges;
      info.p_edges_ = & p_edges;

      option.intf->on_update(info);
    }
    count++;
  } // iter
  return chi2;
}
