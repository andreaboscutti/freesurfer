/**
 * @file  mrilabels_cuda.hpp
 * @brief Holds various MRI label routines for the GPU
 *
 */
/*
 * Original Author: Richard Edgar
 * CVS Revision Info:
 *    $Author: rge21 $
 *    $Date: 2011/03/24 18:33:55 $
 *    $Revision: 1.4 $
 *
 * Copyright (C) 2002-2008,
 * The General Hospital Corporation (Boston, MA). 
 * All rights reserved.
 *
 * Distribution, usage and copying of this software is covered under the
 * terms found in the License Agreement file named 'COPYING' found in the
 * FreeSurfer source code root directory, and duplicated here:
 * https://surfer.nmr.mgh.harvard.edu/fswiki/FreeSurferOpenSourceLicense
 *
 * General inquiries: freesurfer@nmr.mgh.harvard.edu
 * Bug reports: analysis-bugs@nmr.mgh.harvard.edu
 *
 */


#ifndef MRI_LABELS_CUDA_HPP
#define MRI_LABELS_CUDA_HPP

#include "mri.h"
#include "mriframegpu.hpp"
#include "ctfactory.hpp"

namespace GPU {
  namespace Algorithms {

    //! Class to perform various label things on MRIs
    class MRIlabels {
    public:

      //! Constructor
      MRIlabels( void ) {};

      //! Destructor
      ~MRIlabels( void ) {};

      static void ShowTimings( void );

      // --------------------------------------

      template<typename T>
      void MarkLabelBorderVoxels( const GPU::Classes::MRIframeGPU<T>& src,
				  GPU::Classes::MRIframeGPU<unsigned char>& dst,
				  const int label,
				  const int mark,
				  const int sixConnect ) const;

      template<typename T>
      void MLBVdispatch( const MRI* mri_src,
                         MRI* mri_dst,
                         int label,
                         int mark,
                         int six_connected ) const;



      template<typename T,typename U>
      float VoxInLabelWithPartialVolume( const GPU::Classes::MRIframeGPU<T>& mri,
					 const GPU::Classes::MRIframeGPU<U>& mri_vals,
					 const int label,
					 GPU::Classes::MRIframeGPU<float>& mri_mixing_coeff,
					 GPU::Classes::MRIframeGPU<unsigned char>& mri_nbr_labels ) const;
					 

      template<typename T, typename U>
      float ViLwpVfinalDispatch( const MRI *mri,
                                 const MRI *mri_vals, 
                                 const int label,
                                 MRI *mri_mixing_coef, 
                                 MRI *mri_nbr_labels ) const;
      

      template<typename T>
      float ViLwpVvalsDispatch( const MRI *mri,
                                const MRI *mri_vals, 
                                const int label,
                                MRI *mri_mixing_coef, 
                                MRI *mri_nbr_labels ) const;

      // --------------------------------------
    private:

      // Timers
      static SciGPU::Utilities::Chronometer tMarkLabelBorderVoxelsTot;

      static SciGPU::Utilities::Chronometer tVoxInLabelPartVolumeTot;
      static SciGPU::Utilities::Chronometer tVoxInLabelPartVolumeCompute;

      // ---------

      //! Suppress copy constructor
      MRIlabels( const MRIlabels& src ) {
	std::cerr << __FUNCTION__
		  << ": Please do not copy" << std::endl;
	abort();
      }

      //! Suppress assignment operator
      MRIlabels& operator=( const MRIlabels& src ) {
	std::cerr << __FUNCTION__
		  << ": Please do not copy" << std::endl;
	abort();
      }


      // ------------

      //! Texture handling
      template<typename T>
      GPU::Classes::CTfactory* BindMRI( const GPU::Classes::MRIframeGPU<T>& src ) const {
        std::cerr << __PRETTY_FUNCTION__
                  << ": Unrecognised type"
                  << std::endl;
        abort();
        return( NULL );
      }

      template<typename T>
      GPU::Classes::CTfactory* BindMRIvals( const GPU::Classes::MRIframeGPU<T>& src ) const {
        std::cerr << __PRETTY_FUNCTION__
                  << ": Unrecognised type"
                  << std::endl;
        abort();
        return( NULL );
      }


      template<typename T>
      GPU::Classes::CTfactory* BindSrc( const GPU::Classes::MRIframeGPU<T>& src ) const {
        std::cerr << __PRETTY_FUNCTION__
                  << ": Unrecognised type"
                  << std::endl;
        abort();
        return( NULL );
      }

    };

  }
}


#endif
