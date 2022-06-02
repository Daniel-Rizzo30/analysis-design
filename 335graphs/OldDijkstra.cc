    /* Old Dijkstra's Algortihm - doesn't work but I'm just keeping this. 
    void Dijkstra(int start_vertex) {
        for (size_t i = 0; i < Adjacency_List_.size(); i++) {
            Adjacency_List_[i].previous_in_path_ = infinity_;
            Adjacency_List_[i].cost_ = infinity_;
            Adjacency_List_[i].known_ = false;
        }

        Adjacency_List_[start_vertex - 1].previous_in_path_ = start_vertex;
        Adjacency_List_[start_vertex - 1].cost_ = 0;
        Adjacency_List_[start_vertex - 1].known_ = true;
        BinaryHeap<Edge> Q1(Edge().toVector(Adjacency_List_[start_vertex - 1].adjacency_));

        //BinaryHeap<Edge> Q1(Edge(start_vertex, 0));
        while (true) {

            if (Q1.isEmpty()) break;
            int v = Q1.findMin().in_vertex_;
            double c = Q1.findMin().cost_; // //
            cout << v << endl;
            Q1.deleteMin();
            Adjacency_List_[v - 1].known_ = true;
            Adjacency_List_[v - 1].cost_ = c; // //

            for (std::list<Edge>::iterator it = Adjacency_List_[v - 1].adjacency_.begin(); 
                    it != Adjacency_List_[v - 1].adjacency_.end(); ++it) { 
                int w = it->in_vertex_ ;
                double d = it->cost_;
                if (!Adjacency_List_[w - 1].known_) {
                    const double new_dist = Adjacency_List_[v - 1].cost_ + d;
                    if (new_dist < Adjacency_List_[w - 1].cost_) {
                        //if (Adjacency_List_[w - 1].cost_ == INFINITY) {
                            Adjacency_List_[w - 1].cost_ = new_dist;
                            vector<Edge> w_adjacency = toVector(Adjacency_List_[w - 1].adjacency_);
                            for (std::list<Edge>::iterator it = Adjacency_List_[w - 1].adjacency_.begin(); 
                                    it != Adjacency_List_[w - 1].adjacency_.end(); ++it) { 
                                Q1.insert(*it);
                            }
                            //Q1.insert()
                        //}
                        //else {
                            //SetKey???
                        //}
                        Adjacency_List_[w - 1].previous_in_path_ = v;
                    }
                }  
            }
        }
    }*/
