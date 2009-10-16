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




#if !defined(AFX_SLICEHEADER_H__G31F1842_FFCD_42AD_A981_7BD2736A4431__INCLUDED_)
#define AFX_SLICEHEADER_H__G31F1842_FFCD_42AD_A981_7BD2736A4431__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "H264AVCCommonLib/SliceHeaderBase.h"



H264AVC_NAMESPACE_BEGIN


class FrameUnit;


#if defined( WIN32 )
# pragma warning( disable: 4275 )
# pragma warning( disable: 4251 )
#endif


class H264AVCCOMMONLIB_API SliceHeader
: public SliceHeaderBase
, protected CostData
{
public:
	SliceHeader         ( const SequenceParameterSet& rcSPS,
                        const PictureParameterSet&  rcPPS );
	virtual ~SliceHeader();

    Void getMbPositionFromAddress( UInt& ruiMbY, UInt& ruiMbX, const UInt uiMbAddress ) const; 
    Void getMbPositionFromAddress( UInt& ruiMbY, UInt& ruiMbX, UInt& ruiMbIndex, const UInt uiMbAddress ) const ;
    UInt getMbIndexFromAddress( UInt uiMbAddress ) const; //th

#ifdef   LF_INTERLACE
  ErrVal  compare     ( const SliceHeader*          pcSH,
      Bool&                       rbNewPic,
      Bool&                       rbNewFrame ) const;
#else //!LF_INTERLACE
  ErrVal  compare     ( const SliceHeader*          pcSH,
      Bool&                       rbNewFrame ) const;
#endif //LF_INTERLACE

// JVT-Q054 Red. Picture {
  ErrVal  compareRedPic     ( const SliceHeader*          pcSH,
                              Bool&                       rbNewFrame ) const;
  ErrVal  sliceHeaderBackup ( SliceHeader*                pcSH       );
// JVT-Q054 Red. Picture }


  Bool    isIntra     ()  const   { return m_eSliceType == I_SLICE; }
  Bool    isInterP    ()  const   { return m_eSliceType == P_SLICE; }
  Bool    isInterB    ()  const   { return m_eSliceType == B_SLICE; }

#ifdef   LF_INTERLACE
  Bool    isMbAff     ()  const   { return ( ! getFieldPicFlag() && getSPS().getMbAdaptiveFrameFieldFlag() ); }  // for future use

  const RefPicList<RefPic>& getRefPicList( PicType ePicType, ListIdx eListIdx ) const
  {
      return m_aacRefPicList[ePicType-1][eListIdx];
  }
  RefPicList<RefPic>& getRefPicList( PicType ePicType, ListIdx eListIdx )
  {
      return m_aacRefPicList[ePicType-1][eListIdx];
  }
  UInt  getRefListSize( ListIdx eListIdx ) const
  {
      return m_aacRefPicList[getPicType()-1][eListIdx].size();
  }
  const RefPic& getRefPic( UInt uiFrameId, PicType ePicType, ListIdx eLstIdx ) const
  {
      uiFrameId--;
      AOT_DBG( eLstIdx > 2 );
      return m_aacRefPicList[ePicType-1][eLstIdx].get( uiFrameId );
  }
  Void  setRefFrameList ( RefFrameList* pc,
      PicType       ePicType,
      ListIdx       eListIdx  )  
  { 
	  m_aapcRefFrameList[ePicType-1][eListIdx]  = pc; 
  }

  Void  setTopFieldPoc  ( Int           i  )  { m_iTopFieldPoc        = i;  }
  Void  setBotFieldPoc  ( Int           i  )  { m_iBotFieldPoc        = i;  }
#else //!LF_INTERLACE
  const RefPicList<RefPic>& getRefPicList( ListIdx eListIdx ) const
  {
      return m_acRefPicList[eListIdx];
  }
  RefPicList<RefPic>& getRefPicList( ListIdx eListIdx )
  {
      return m_acRefPicList[eListIdx];
  }
  UInt  getRefListSize( ListIdx eListIdx ) const
  {
      return m_acRefPicList[eListIdx].size();
  }
  const RefPic& getRefPic( UInt uiFrameId, ListIdx eLstIdx ) const
  {
      uiFrameId--;
      AOT_DBG( eLstIdx > 2 );
      return m_acRefPicList[eLstIdx].get( uiFrameId );
  }
#endif


  Void  setPoc          ( Int           i  )  { m_iPoc                = i; }
  Void  setLastMbInSlice( UInt          ui )  { m_uiLastMbInSlice     = ui; }
  Void  setFrameUnit    ( FrameUnit*    pc )  { m_pcFrameUnit         = pc; }
  Void  setRefFrameList ( RefFrameList* pc,
                          ListIdx       e  )  { m_apcRefFrameList[e]  = pc; }

#ifdef   LF_INTERLACE
  Int             getTopFieldPoc        ()                    const { return m_iTopFieldPoc; }
  Int             getBotFieldPoc        ()                    const { return m_iBotFieldPoc; }
  Int             getPoc            ()                    const { return ( m_bFieldPicFlag ? ( m_bBottomFieldFlag ? m_iBotFieldPoc : m_iTopFieldPoc ) : min( m_iTopFieldPoc, m_iBotFieldPoc ) ); }
  Int             getPoc            ( PicType ePicType )  const { return ( ePicType == FRAME ? min( m_iTopFieldPoc, m_iBotFieldPoc ) : ePicType == BOT_FIELD ? m_iBotFieldPoc : m_iTopFieldPoc ); }
  Void             setPoc            ( UInt poc, PicType ePicType ) 
                   { 
					   if( ePicType == BOT_FIELD )
					   { m_iBotFieldPoc=poc; }
					   else if(ePicType == TOP_FIELD )
					   {m_iTopFieldPoc=poc ; }
                    }
  RefFrameList*   getRefFrameList       ( PicType ePicType,
      ListIdx eLstIdx )   const { return m_aapcRefFrameList[ePicType-1][eLstIdx]; }
#else
    Int             getPoc                ()                    const { return m_iPoc; }
#endif

  UInt            getLastMbInSlice      ()                    const { return m_uiLastMbInSlice; }
  FrameUnit*      getFrameUnit          ()                    const { return m_pcFrameUnit; }
  FrameUnit*      getFrameUnit          ()                          { return m_pcFrameUnit; }
  RefFrameList*   getRefFrameList       ( ListIdx eLstIdx )   const { return m_apcRefFrameList[eLstIdx]; }
  CostData&       getCostData           ()                          { return *this; }
  const CostData& getCostData           ()                    const { return *this; }
  UChar           getChromaQp           ( UChar   ucLumaQp )  const { return g_aucChromaScale[ gClipMinMax( ucLumaQp + getPPS().getChomaQpIndexOffset(), 0, 51 ) ];}
  const Bool      isScalingMatrixPresent( UInt    uiMatrix )  const { return NULL != m_acScalingMatrix.get( uiMatrix ); }
  const UChar*    getScalingMatrix      ( UInt    uiMatrix )  const { return m_acScalingMatrix.get( uiMatrix ); }
  
#ifdef   LF_INTERLACE
  Int             getDistScaleFactor    ( PicType eMbPicType,
      SChar   sL0RefIdx,
      SChar   sL1RefIdx ) const;
  Int             getDistScaleFactorScal( PicType eMbPicType,
      SChar   sL0RefIdx,
      SChar   sL1RefIdx ) const;

  //	TMM_EC {{
  Int             getDistScaleFactorVirtual( PicType eMbPicType,
      SChar   sL0RefIdx,
      SChar   sL1RefIdx,
      RefFrameList& rcRefFrameListL0, 
      RefFrameList& rcRefFrameListL1 ) const;
  //  TMM_EC }}
#else //!LF_INTERLACE
  Int             getDistScaleFactor    ( SChar   sL0RefIdx,
      SChar   sL1RefIdx ) const;
//	TMM_EC {{
  Int             getDistScaleFactorVirtual( SChar   sL0RefIdx,
      SChar   sL1RefIdx,
      RefFrameList& rcRefFrameListL0, 
      RefFrameList& rcRefFrameListL1 ) const;
//  TMM_EC }}
  Int             getDistScaleFactorScal( SChar   sL0RefIdx,
                                          SChar   sL1RefIdx ) const;
#endif //LF_INTERLACE

  Int             getDistScaleFactorWP  ( const Frame*    pcFrameL0, const Frame*     pcFrameL1 )  const;
  Int             getDistScaleFactorWP  ( const IntFrame* pcFrameL0, const IntFrame*  pcFrameL1 )  const;
  Void            setFGSCodingMode      ( Bool b  )            { m_bFGSCodingMode = b;     }
  Void            setGroupingSize       ( UInt ui )            { m_uiGroupingSize = ui;    }
  Void            setPosVect            ( UInt ui, UInt uiVal) { m_uiPosVect[ui]  = uiVal; }
  Bool            getFGSCodingMode      ()                     { return m_bFGSCodingMode;  }
  UInt            getGroupingSize       ()                     { return m_uiGroupingSize;  }
  UInt            getPosVect            ( UInt ui )            { return m_uiPosVect[ui];   }

protected:
  ErrVal          xInitScalingMatrix    ();


protected:
#ifdef   LF_INTERLACE
    RefPicList<RefPic>      m_aacRefPicList[3][2];
    RefFrameList*           m_aapcRefFrameList[3][2];
    Int                     m_iTopFieldPoc;
    Int                     m_iBotFieldPoc;
#endif
    RefPicList<RefPic>      m_acRefPicList[2];
    Int                     m_iPoc;
  UInt                    m_uiLastMbInSlice;
  FrameUnit*              m_pcFrameUnit;
  StatBuf<const UChar*,8> m_acScalingMatrix;
  RefFrameList*           m_apcRefFrameList[2];
  Bool                    m_bFGSCodingMode;
  UInt                    m_uiGroupingSize;
  UInt                    m_uiPosVect[16];
};


#if defined( WIN32 )
# pragma warning( default: 4251 )
# pragma warning( default: 4275 )
#endif


typedef SliceHeader::DeblockingFilterParameter DFP;



H264AVC_NAMESPACE_END


#endif // !defined(AFX_SLICEHEADER_H__G31F1842_FFCD_42AD_A981_7BD2736A4431__INCLUDED_)
