#include "../include/optimizer.h"
#include "../include/optimizer_types.h"

template<typename T>
T test_optimize(TestCase test_case){
    Sophus::SE2<T> g_0w = Sophus::SE2<T>(0.3f, Eigen::Matrix<T,2,1>(1.f,2.f)).inverse();
    PoseSE2<T>* f0 = new PoseSE2<T>(g_0w);
    f0->fix(true);

    Sophus::SE2<T> g_1w       = Sophus::SE2<T>(20.f/180.f*3.141592f, Eigen::Matrix<T,2,1>(2.f,  0.5f)).inverse();
    Sophus::SE2<T> g_1w_noisy = Sophus::SE2<T>(30.f/180.f*3.141592f, Eigen::Matrix<T,2,1>(2.5f,  2.f)).inverse();
    std::cout<< "true g_cw= \n" << g_1w.matrix2x3() << std::endl;
    std::cout<< "init g_cw= \n" << g_1w_noisy.matrix2x3() << std::endl;
    PoseSE2<T>* f1 = new PoseSE2<T>(g_1w_noisy);

    std::set<OptNode<T>*> frames = {f1};
    std::set<OptNode<T>*> points;
    std::set<OptEdge<T>*> edges;
    T offset = 5.f;
    for(size_t i = 0; i < 10; i++){
        Eigen::Matrix<T,2,1> x_0(20.f, -5.f + (T)i);
        if(std::abs(x_0.y()) < 3.f)
            x_0.y() = (x_0.y()>0?1.f:-1.f) * 3.f;
        Eigen::Matrix<T,2,1> x_w = g_0w.inverse() * x_0;
        Eigen::Matrix<T,2,1> x_c = g_1w * x_w;
        T uv0 = ProjSE2Edge<T>::proj(x_0);
        T z   = ProjSE2Edge<T>::proj(x_c);
        T rho = 1.f / x_0.x();
        rho *= 1.2f; // noisy intialization
        T disparity = ProjDisparitySE2Edge<T>::disparity(x_0, offset);
        Point2<T>*   pt   = new Point2<T>(f0, uv0, rho);
        ProjSE2Edge<T>* proj_edge = new ProjSE2Edge<T>(f1, pt, z);
        ProjDisparitySE2Edge<T>* disparity_edge = new ProjDisparitySE2Edge<T>(&offset, pt, disparity);
        edges.insert(proj_edge);
        edges.insert(disparity_edge);
        points.insert(pt);
    }

    OptimizeBAOption<T> option;
    option.n_iter = 10;
    T chi2 = 99999999.f;
    std::set<OptNode<T>*> nodes; // merge frames/points
    nodes.insert(frames.begin(), frames.end());
    nodes.insert(points.begin(), points.end());

    if( test_case == TestCase::BA_OPTIMIZATION){
        size_t point_dim = 1;
        chi2 = optimize_ba<T>(point_dim, frames, points, option);
    }
    std::cout << "g_cw = \n" << f1->g_cw().matrix2x3() << std::endl;
    printf("before delete, ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    delete f0;
    for(auto it = nodes.begin(); it !=nodes.end(); it++){
        OptNode<T>* node = *it;
        delete node;
    }
    printf("after  delete, ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    if(OptEdge<T>::n_instance()>0 || OptNode<T>::n_instance()){
        printf("Error : node or edge remove failure\n");
        throw 1;
    }
    if(chi2 > 1e-5){
        printf("Error : optimmize test %d failure, chi2= %e\n", test_case, chi2);
        throw 1;
    }
    return chi2;
}

template<typename T>
void se2_marginalization_test() {
    std::default_random_engine generator;
    std::uniform_real_distribution<T> y0_distribution(-6.0, 6.0);
    std::uniform_real_distribution<T> x0_distribution(5.0, 7.0);
    std::vector<Sophus::SE2<T>*> gt_poses;
    std::vector<Eigen::Matrix<T,2,1>*> gt_points;
    std::vector<int> j0_points; // j0 of points


    std::vector<T> headings= {10.f, 20.f, 15.f, 20.f, 25.f, 10.f};
    std::vector<T> arr_y   = { 1.f, 1.5f, -2.f,  3.f,  5.f, 15.f};
    //int n_frames = 3;
    int n_frames = headings.size();
    headings.erase(headings.begin() + n_frames, headings.end());
    arr_y.erase(arr_y.begin() + n_frames, arr_y.end());
    const int n_create = 10;
    for(int j = 0; j < static_cast<int>(headings.size()); j++){
        T x = 10.f * j;
        T y = arr_y.at(j);
        Sophus::SE2<T>* cw = new Sophus::SE2<T>();
        gt_poses.push_back(cw);
        *cw = Sophus::SE2<T>(headings.at(j)/180.f*3.141592, Eigen::Matrix<T,2,1>(x,y));
        // 매 프레임 10개의 점이 새로 추가된다.
        // 점은 3프레임동안 유지된다.
        if(j+1 < static_cast<int>(headings.size()) ){
            for(int i = 0; i < n_create; i++){
                T x0 = x0_distribution(generator);
                T y0 = 0.f;
                while(std::abs(y0) < 2.f)
                    y0 = y0_distribution(generator);
                Eigen::Matrix<T,2,1>* pt = new Eigen::Matrix<T,2,1>(x0,y0);
                gt_points.push_back(pt);
                j0_points.push_back(j);
            }
        }
    }
    T offset = - 2.f;
    std::set<OptNode<T>*> frames;
    std::vector<PoseSE2<T>*> frames_seq;
    std::set<OptNode<T>*> points;
    std::set<OptEdge<T>*> edges;
    OptNode<T>* mg_f = NULL;

    for(int j = 0; j < n_frames; j++){
        Sophus::SE2<T> gt_cw = * gt_poses.at(j);
        Sophus::SE2<T> cw = Sophus::SE2<T>(0.05f, Eigen::Matrix<T,2,1>(1.f, 1.f)) * gt_cw;
        PoseSE2<T>* node = new PoseSE2<T>(cw);
        frames.insert(node);
        frames_seq.push_back(node);
        if(j==0) node->fix(true);
        else if(j==1) mg_f = node;
    }

    for(size_t i = 0; i < gt_points.size(); i++){
        Eigen::Matrix<T,2,1> x0 = *gt_points.at(i);
        T uv0 = ProjSE2Edge<T>::proj(x0);
        T rho = 1.f / x0.x();
        rho *= 1.2; // noise
        int j0 = j0_points.at(i);
        PoseSE2<T>* f0 = frames_seq.at(j0);
        Point2<T>* pt = new Point2<T>(f0, uv0, rho);
        points.insert(pt);
        T disparity = ProjDisparitySE2Edge<T>::disparity(x0, offset);
        ProjDisparitySE2Edge<T>* disparity_edge = new ProjDisparitySE2Edge<T>(&offset, pt, disparity);
        edges.insert(disparity_edge);
        Sophus::SE2<T> gt_0w = *gt_poses.at(j0);
        Eigen::Matrix<T,2,1> xw = gt_0w.inverse() * x0;


        for(int j = j0+1; j < j0+3; j++){
            if(j >= static_cast<int>(gt_poses.size()))
                break;
            Sophus::SE2<T> gt_cw = *gt_poses.at(j);
            Eigen::Matrix<T,2,1> xc = gt_cw * xw;
            T z = ProjSE2Edge<T>::proj(xc);
            PoseSE2<T>* fj = frames_seq.at(j);
            ProjSE2Edge<T>* proj_edge = new ProjSE2Edge<T>(fj, pt, z);
            edges.insert(proj_edge);
        }
    }

    std::set<OptNode<T>*> nodes;
    nodes.insert(frames.begin(), frames.end());
    nodes.insert(points.begin(), points.end());


    OptimizeBAOption<T> option;
    OptInterface<T> intf;
    option.intf = & intf;
    option.n_iter = 10;
    T chi2 = 999999999.;
    size_t point_dim = 1;

    if(true)
        chi2 = optimize_ba<T>(point_dim, frames, points, option);
    {
        GeneralOptMarginals<T> marginals;
        // Test : marginalize f0
        std::set<OptNode<T>*> mg_points;
        for(auto it = mg_f->edges().begin(); it != mg_f->edges().end(); it++){
            OptEdge<T>* e = *it;
            if(e->type() != OptEdge<T>::F2P) continue;
            OptNode<T>* pt = e->nodes().at(1);;
            mg_points.insert(pt);
        }
        for(auto it = mg_points.begin(); it != mg_points.end(); it++){
            OptNode<T>* pt = *it;
            marginals.marginalize_point(pt, true);
            pt->fix(true);
            if(pt->edges().size()>0){
                printf("Error : edge remove failure\n");
                throw 1;
            }
        }
        marginals.marginalize_frame(mg_f, true);
        if(mg_f->edges().size()>0){
            printf("Error : edge remove failure\n");
            throw 1;
        }
        mg_f->fix(true); // marginalized 되었으니까.
        option.marginals = &marginals;
        chi2 = optimize_ba(point_dim, frames, points, option);
    }
    printf("before delete 'Nodes', ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
    printf("after delete 'Nodes', ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    for(auto it = gt_poses.begin(); it != gt_poses.end(); it++){
        auto ptr = *it;
        delete ptr;
    }
    for(auto it = gt_points.begin(); it != gt_points.end(); it++){
        auto ptr = *it;
        delete ptr;
    }
    if(chi2 > 1e-2){
        printf("Error : optimmize_ba failure, chi2= %e\n", chi2);
        throw 1;
    }
}

template<typename T>
void se3_marginalization_test(){
    std::default_random_engine generator;
    std::uniform_real_distribution<T> xy_distribution(-6.0, 6.0);
    std::uniform_real_distribution<T> z_distribution(5.0, 7.0);

    auto donut_generate = [&generator,&xy_distribution]()->T{ T v;
        while(1){
            v = xy_distribution(generator);
            if(std::abs(v) > 1.f) break;
        } return v;
    };

    std::vector<Sophus::SE3<T>, Eigen::aligned_allocator<Sophus::SE3<T>> > gt_poses;
    std::vector<Eigen::Matrix<T,3,1>, Eigen::aligned_allocator<Eigen::Matrix<T,3,1>> > gt_points;
    std::vector<int> j0_points;
    std::vector<T> headings= {10.f, 20.f, 15.f, 20.f, 25.f, 10.f};
    std::vector<T> arr_y   = { 1.f, 1.5f, -2.f,  3.f,  5.f, 15.f};
    int n_frames = 5;
    //int n_frames = headings.size();
    headings.erase(headings.begin() + n_frames, headings.end());
    arr_y.erase(arr_y.begin() + n_frames, arr_y.end());
    const int n_create = 10;
    for(size_t j = 0; j < headings.size(); j++){
        T z = 10.f * j;
        T y = arr_y.at(j);
        Sophus::SE3<T> cw;
        cw.translation() = Eigen::Matrix<T,3,1>(0.,y,z);
        T yaw = headings.at(j)/180.*3.141592;
        T pitch = 0.5*yaw;
        cw.rotX(pitch);
        cw.rotY(yaw);
        gt_poses.push_back(cw);
        if(j+1 < headings.size()){
            for(size_t i = 0; i < n_create; i++){
                T x0 = donut_generate();
                T y0 = donut_generate();
                T z0 = z_distribution(generator);
                Eigen::Matrix<T,3,1> pt(x0,y0, z0);
                gt_points.push_back(pt);
                j0_points.push_back(j);
            }
        }
    }
    T offset = - 2.;
    Sophus::SE3<T> noise;
    noise.translation() = Eigen::Matrix<T,3,1>(0.5,0.5,1.);

    std::set<OptNode<T>*> frames, points;
    std::vector<PoseSE3<T>*> frames_seq;
    std::set<OptEdge<T>*> edges;
    OptNode<T>* mg_f = NULL;
    for(int j = 0; j < n_frames; j++){
        const Sophus::SE3<T>& gt_cw = gt_poses.at(j);
        Sophus::SE3<T> cw = noise * gt_cw;
        PoseSE3<T>* node = new PoseSE3<T>(cw, ExpMult::PRE);
        frames.insert(node);
        frames_seq.push_back(node);
        if(j==0) node->fix(true);
        else if (j==1) mg_f = node;
    }

    for(size_t i = 0; i < gt_points.size(); i++){
        Eigen::Matrix<T,3,1> x0 = gt_points.at(i);
        Eigen::Matrix<T,2,1> uv0 = ProjSE3Edge<T>::proj(x0);
        T rho = 1. / x0.z();
        rho *= 1.2; // noise
        int j0 = j0_points.at(i);
        PoseSE3<T>* f0 = frames_seq.at(j0);
        Point3<T>* pt = new Point3<T>(f0, uv0, rho);
        points.insert(pt);
        T disparity = ProjDisparitySE3Edge<T>::disparity(x0, offset);
        ProjDisparitySE3Edge<T>* disparity_edge = new ProjDisparitySE3Edge<T>(&offset, pt, disparity);
        edges.insert(disparity_edge);
        Sophus::SE3<T> gt_0w = gt_poses.at(j0);
        Eigen::Matrix<T,3,1> xw = gt_0w.inverse() * x0;
        for(int j = j0+1; j < j0+3; j++){
            if(j >= static_cast<int>(gt_poses.size()))
                break;
            Sophus::SE3<T> gt_cw = gt_poses.at(j);
            Eigen::Matrix<T,3,1> xc = gt_cw * xw;
            Eigen::Matrix<T,2,1> z = ProjSE3Edge<T>::proj(xc);
            PoseSE3<T>* fj = frames_seq.at(j);
            ProjSE3Edge<T>* proj_edge = new ProjSE3Edge<T>(fj, pt, z);
            edges.insert(proj_edge);
        }
    }
    std::set<OptNode<T>*> nodes;
    nodes.insert(frames.begin(), frames.end());
    nodes.insert(points.begin(), points.end());
    OptimizeBAOption<T> option;
    OptInterface<T> intf;
    option.intf = & intf;
    option.n_iter = 10;
    T chi2 = 999999999.;
    size_t point_dim = 1;
    if(true)
        chi2 = optimize_ba<T>(point_dim, frames, points, option);
    {
        GeneralOptMarginals<T> marginals;
        std::set<OptNode<T>*> mg_points;
        for(auto it = mg_f->edges().begin(); it != mg_f->edges().end(); it++){
            OptEdge<T>* e = *it;
            if(e->type() != OptEdge<T>::F2P) continue;
            OptNode<T>* pt = e->nodes().at(1);
            mg_points.insert(pt);
        }
        for(auto it = mg_points.begin(); it != mg_points.end(); it++){
            OptNode<T>* pt = *it;
            marginals.marginalize_point(pt, true);
            if(pt->edges().size()>0){
                printf("Error : edge remove failure\n");
                throw 1;
            }
            pt->fix(true);
        }
        marginals.marginalize_frame(mg_f, true);
        if(mg_f->edges().size()>0){
            printf("Error : edge remove failure\n");
            throw 1;
        }
        mg_f->fix(true); // marginalized 되었으니까.
        option.marginals = &marginals;
        chi2 = optimize_ba(point_dim, frames, points, option);
    }
    printf("before delete 'Nodes', ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    for(auto it = nodes.begin(); it != nodes.end(); it++)
        delete *it;
    printf("after  delete 'Nodes', ");
    printf("n(Node)=%3d, ", OptNode<T>::n_instance());
    printf("n(Edge)=%3d\n", OptEdge<T>::n_instance());
    if(OptEdge<T>::n_instance()>0 || OptNode<T>::n_instance()){
        printf("Error : node or edge remove failure\n");
        throw 1;
    }
    if(chi2 > 1e-2){
        printf("Error : optimmize_ba failure, chi2= %e\n", chi2);
        throw 1;
    }
}

void optimizer_test(){
    typedef float T;
    OptNode<T>::set_print_create_destruct(false);
    OptEdge<T>::set_print_create_destruct(false);
    std::vector<TestCase> test_list = {BA_OPTIMIZATION,
        SE2_MARGINALIZATION, SE3_MARGINALIZATION};
    for(auto it = test_list.begin(); it!=test_list.end(); it++){
        if(*it == SE2_MARGINALIZATION)
            se2_marginalization_test<T>();
        else if(*it == SE3_MARGINALIZATION)
            se3_marginalization_test<T>();
        else
            test_optimize<T>(*it);
    }
    printf("Every test is success\n");
}
