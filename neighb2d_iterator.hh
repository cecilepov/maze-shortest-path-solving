#ifndef NEIGHB2D_ITERATOR_HH
#define NEIGHB2D_ITERATOR_HH

#include "point2d.hh"
#include "box2d.hh"

#include <vector>
#include <limits>

namespace project_namespace
{
    class neighb2d_iterator
    {
        public:

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */

            neighb2d_iterator(const point2d& pt)
            {
                neighborhood_.resize(4);
                center_at(pt);
            }

            ~neighb2d_iterator()
            {
            }

            void center_at(const point2d& pt)
            {
                current_pt_ = pt;
                current_neighbor_pos_ = 0;
                int row = pt.get_row();
                int col = pt.get_col();

                // neighborhood_.push_back(point2d(row-1, col)); //p1 = top
                // neighborhood_.push_back(point2d(row, col-1)); //p2 = left
                // neighborhood_.push_back(point2d(row, col+1)); //p3 = right
                // neighborhood_.push_back(point2d(row+1, col)); //p4 = bottom

                point2d p1 = point2d(row, col-1);
                point2d p2 = point2d(row-1, col);
                point2d p3 = point2d(row+1, col);
                point2d p4 = point2d(row, col+1);
                neighborhood_[0] = p1;
                neighborhood_[1] = p2;
                neighborhood_[2] = p3;
                neighborhood_[3] = p4;


            }


            //***********************************************************************
            /* MEMBER FUNCTIONS */

            /* Member functions for iteration */

            point2d start()
            {
                current_neighbor_pos_ = 0;
                return neighborhood_[0];
            }

            point2d next()
            {
                current_neighbor_pos_ = current_neighbor_pos_ + 1;
                return neighborhood_[current_neighbor_pos_]; //at : better than [] because it verifies limits
            }

            bool is_valid() const
            {
                return current_neighbor_pos_ <= 3;
            }

            bool is_done() const
            {
                return current_neighbor_pos_ >= 4;
            }

            //***********************************************************************
            /* GETTERS AND SETTERS */

            point2d get_current_pt() const
            {
                return current_pt_;
            }


        private:
            std::vector<point2d> neighborhood_;
            unsigned current_neighbor_pos_; //current index in neighborhood
            point2d current_pt_; // center point p

    };

}

#endif
