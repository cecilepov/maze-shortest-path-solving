#ifndef BOX2D_HH
#define BOX2D_HH

#include <iostream>
#include <vector>
#include <limits>

#include "point2d.hh"


namespace project_namespace
{

	//forward declaration, required for the 2 "using" in the class below
	class box2d_iterator;
	class neighb2d_iterator;

	class box2d
	{
		public:
			using p_iterator_type = box2d_iterator; 
			using n_iterator_type = neighb2d_iterator;

            //***********************************************************************
            /* CONSTRUCTORS AND DESTRUCTORS */
        
            /* Constructor of class box2d */
			box2d(const point2d& start_pt, const point2d& end_pt)
			: start_pt_(start_pt) //start_pt_ : upper left point in the box
			, end_pt_(end_pt)     //end_pt_ : lower right point in the box
			{
			}

            /* Destructor of class box2d */
			~box2d()
			{
			}

			//***********************************************************************
			/* MEMBER FUNCTIONS */

			/* Check if a point is included in the domain defined by the box2d object */

			bool has(const point2d& pt) const //so that 0 variable is modified in the body of the member function
			{
				int pt_row = pt.get_row();
				int pt_col = pt.get_col();
				bool has_row = (this->get_start_pt_row() <= pt_row) && (this->get_end_pt_row() >= pt_row);
				bool has_col = (this->get_start_pt_col() <= pt_col) && (this->get_end_pt_col() >= pt_col);
				return has_row && has_col; // return true if the point in included in the domain
			}


			//***********************************************************************
            /* GETTERS AND SETTERS */

			/* Coordinates */

			int get_start_pt_row() const
			{
				return start_pt_.get_row();	
			}

			int get_start_pt_col() const
			{
				return start_pt_.get_col();
			}

			int get_end_pt_row() const
			{
				return end_pt_.get_row();	
			}

			int get_end_pt_col() const
			{
				return end_pt_.get_col();	
			}



			/* Getter for points */

			point2d get_start_pt() const
			{
				return start_pt_;	
			}

			point2d get_end_pt() const
			{
				return end_pt_;	
			}



			/* Return dimensions of the box2d */

			unsigned get_nbrows() const
			{
				unsigned nbrows = end_pt_.get_row() - start_pt_.get_row() +1; //indexes start at 0
				return nbrows;
			}

			unsigned get_nbcols() const
			{
				unsigned nbcols = end_pt_.get_col() - start_pt_.get_col() +1; //indexes start at 0
				return nbcols;
			}

			unsigned get_nbpoints() const 
			{
				unsigned nbrows = this->get_nbrows();
				unsigned nbcols = this->get_nbcols();
				return nbrows * nbcols;
			}

		 // end public functions
		 
		private:
			point2d start_pt_;
			point2d end_pt_; 

	}; 
}

#endif


