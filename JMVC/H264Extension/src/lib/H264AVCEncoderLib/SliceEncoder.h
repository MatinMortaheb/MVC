/*
********************************************************************************

NOTE - One of the two copyright statements below may be chosen
       that applies for the software.

********************************************************************************

This software module was originally developed by

Heiko Schwarz    (Fraunhofer HHI),
Tobias Hinz      (Fraunhofer HHI),
Karsten Suehring (Fraunhofer HHI)

in the course of development of the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video
Coding) for reference purposes and its performance may not have been optimized.
This software module is an implementation of one or more tools as specified by
the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding).

Those intending to use this software module in products are advised that its
use may infringe existing patents. ISO/IEC have no liability for use of this
software module or modifications thereof.

Assurance that the originally developed software module can be used
(1) in the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) once the
ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) has been adopted; and
(2) to develop the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding): 

To the extent that Fraunhofer HHI owns patent rights that would be required to
make, use, or sell the originally developed software module or portions thereof
included in the ISO/IEC 14496-10:2005 Amd.1 (Scalable Video Coding) in a
conforming product, Fraunhofer HHI will assure the ISO/IEC that it is willing
to negotiate licenses under reasonable and non-discriminatory terms and
conditions with applicants throughout the world.

Fraunhofer HHI retains full right to modify and use the code for its own
purpose, assign or donate the code to a third party and to inhibit third
parties from using the code for products that do not conform to MPEG-related
ITU Recommendations and/or ISO/IEC International Standards. 

This copyright notice must be included in all copies or derivative works.
Copyright (c) ISO/IEC 2005. 

********************************************************************************

COPYRIGHT AND WARRANTY INFORMATION

Copyright 2005, International Telecommunications Union, Geneva

The Fraunhofer HHI hereby donate this source code to the ITU, with the following
understanding:
    1. Fraunhofer HHI retain the right to do whatever they wish with the
       contributed source code, without limit.
    2. Fraunhofer HHI retain full patent rights (if any exist) in the technical
       content of techniques and algorithms herein.
    3. The ITU shall make this code available to anyone, free of license or
       royalty fees.

DISCLAIMER OF WARRANTY

These software programs are available to the user without any license fee or
royalty on an "as is" basis. The ITU disclaims any and all warranties, whether
express, implied, or statutory, including any implied warranties of
merchantability or of fitness for a particular purpose. In no event shall the
contributor or the ITU be liable for any incidental, punitive, or consequential
damages of any kind whatsoever arising from the use of these programs.

This disclaimer of warranty extends to the user of these programs and user's
customers, employees, agents, transferees, successors, and assigns.

The ITU does not represent or warrant that the programs furnished hereunder are
free of infringement of any third-party patents. Commercial implementations of
ITU-T Recommendations, including shareware, may be subject to royalty fees to
patent holders. Information regarding the ITU-T patent policy is available from 
the ITU Web site at http://www.itu.int.

THIS IS NOT A GRANT OF PATENT RIGHTS - SEE THE ITU-T PATENT POLICY.

********************************************************************************
*/





#if !defined(AFX_SLICEENCODER_H__A0183156_A54B_425D_8CF1_D350651F638C__INCLUDED_)
#define AFX_SLICEENCODER_H__A0183156_A54B_425D_8CF1_D350651F638C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "H264AVCCommonLib/ControlMngIf.h"
#include "H264AVCCommonLib/TraceFile.h"
#include "MbEncoder.h"


H264AVC_NAMESPACE_BEGIN


class CodingParameter;
class MbCoder;
class PocCalculator;


class SliceEncoder
{
protected:
	SliceEncoder();
	virtual ~SliceEncoder();

public:
  static ErrVal create( SliceEncoder*& rpcSliceEncoder );
  ErrVal destroy();
  ErrVal init( MbEncoder* pcMbEncoder,
               MbCoder* pcMbCoder,
               ControlMngIf* pcControlMng,
               CodingParameter* pcCodingParameter,
               PocCalculator* pcPocCalculator,
               Transform* pcTransform);

  ErrVal uninit();

  MbEncoder*  getMbEncoder            () { return m_pcMbEncoder; }



  ErrVal      encodeSlice             ( SliceHeader&  rcSliceHeader,
                                        IntFrame*     pcFrame,
                                        MbDataCtrl*   pcMbDataCtrl,
                                        RefFrameList& rcList0,
                                        RefFrameList& rcList1,
                                        UInt          uiMbInRow,
                                        Double        dlambda	);
#ifdef LF_INTERLACE
  ErrVal      encodeSliceMbAff             ( SliceHeader&  rcSliceHeader,
                                      IntFrame*     pcFrame,
                                      MbDataCtrl*   pcMbDataCtrl,
                                      RefFrameList& rcList0,
                                      RefFrameList& rcList1,
                                      UInt          uiMbInRow,
                                      Double        dlambda	);
#endif//LF_INTERLACE
//TMM_WP
  ErrVal xSetPredWeights( SliceHeader& rcSliceHeader, 
                          IntFrame* pOrgFrame,
                          RefFrameList& rcList0,
                          RefFrameList& rcList1 );


  ErrVal xInitDefaultWeights(Double *pdWeights, 
                             UInt uiLumaWeightDenom, 
                             UInt uiChromaWeightDenom);

//TMM_WP

  //S051{
  Void		setUseBDir			(Bool b){m_pcMbEncoder->setUseBDir(b);}
  //S051}
//JVT-W080
	Void        setPdsEnable              ( UInt   uiValue ) { m_uiPdsEnable                 = uiValue; }
	Void        setPdsInitialDelayMinus2L0( UInt** uiValue ) { m_ppuiPdsInitialDelayMinus2L0 = uiValue; }
	Void        setPdsInitialDelayMinus2L1( UInt** uiValue ) { m_ppuiPdsInitialDelayMinus2L1 = uiValue; }
	Void        setPdsBlockSize           ( UInt   uiValue ) { m_uiPdsBlockSize              = uiValue; }
	UInt        getPdsEnable              ()         const { return m_uiPdsEnable;                  }
	UInt**      getPdsInitialDelayMinus2L0()         const { return m_ppuiPdsInitialDelayMinus2L0;  }
	UInt**      getPdsInitialDelayMinus2L1()         const { return m_ppuiPdsInitialDelayMinus2L1;  }
	UInt        getPdsBlockSize           ()         const { return m_uiPdsBlockSize;               }
//~JVT-W080
protected:
  MbEncoder* m_pcMbEncoder;
  MbCoder* m_pcMbCoder;
  ControlMngIf* m_pcControlMng;
  CodingParameter* m_pcCodingParameter;
  PocCalculator*   m_pcPocCalculator;
  Transform* m_pcTransform;
  Bool m_bInitDone;
  UInt  m_uiFrameCount;
  SliceType m_eSliceType;
  Bool m_bTraceEnable;
//JVT-W080
	UInt   m_uiPdsEnable;
	UInt   m_uiPdsBlockSize;
	UInt** m_ppuiPdsInitialDelayMinus2L0;
	UInt** m_ppuiPdsInitialDelayMinus2L1;
//~JVT-W080

};


H264AVC_NAMESPACE_END


#endif // !defined(AFX_SLICEENCODER_H__A0183156_A54B_425D_8CF1_D350651F638C__INCLUDED_)
