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




#if !defined(AFX_SEQUENCEPARAMETERSET_H__66281283_5BFB_429A_B722_6DDE7A11D086__INCLUDED_)
#define AFX_SEQUENCEPARAMETERSET_H__66281283_5BFB_429A_B722_6DDE7A11D086__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "H264AVCCommonLib/HeaderSymbolReadIf.h"
#include "H264AVCCommonLib/HeaderSymbolWriteIf.h"
#include "H264AVCCommonLib/ScalingMatrix.h"

// TMM_ESS 
#include "ResizeParameters.h"


H264AVC_NAMESPACE_BEGIN



class H264AVCCOMMONLIB_API SpsMvcExtension
{
public:

  SpsMvcExtension()// ying:  add initialization for the construction 
: m_num_views_minus_1         ( 0    )
, m_num_anchor_refs_list0     ( NULL ) 
, m_num_anchor_refs_list1     ( NULL )
, m_num_non_anchor_refs_list0 ( NULL ) 
, m_num_non_anchor_refs_list1 ( NULL ) 
, m_anchor_ref_list0          ( NULL ) 
, m_anchor_ref_list1          ( NULL ) 
, m_non_anchor_ref_list0      ( NULL ) 
, m_non_anchor_ref_list1      ( NULL )
, m_uiViewCodingOrder         ( NULL ) // name ?
, m_bInitDone                 ( false)
, m_num_level_values_signalled_minus1 (0)
, m_ui_level_idc (NULL)
, m_ui_num_applicable_ops_minus1 (NULL)
, m_ui_applicable_op_temporal_id (NULL)
, m_ui_applicable_op_num_target_views_minus1 (NULL)
, m_ui_applicable_op_num_views_minus1 (NULL)
, m_ui_applicable_op_target_view_id (NULL)

  {
  }
  
  //JVT-V054

  ~SpsMvcExtension(){};

//JVT-V054
  UInt* getViewCodingOrder() { return m_uiViewCodingOrder;}
  Bool  getInitDone() {return m_bInitDone;}
  Void  setInitDone(Bool b) { m_bInitDone = b;}

  int getNumViewMinus1() const { return (int)m_num_views_minus_1;}
  Void setNumViewsMinus1(UInt num_views) {m_num_views_minus_1=(int)num_views;}

  int getNumLevelValuesSignalledMinus1() const { return (int)m_num_level_values_signalled_minus1;}
  Void setNumLevelValuesSignalledMinus1(UInt num_level_values_minus1) {m_num_level_values_signalled_minus1=(int)num_level_values_minus1;}

  Void initViewSPSMemory_num_refs_for_lists(UInt num_views_minus1)
  { 
    m_num_anchor_refs_list0 = new int[num_views_minus1+1]; // ue(v)
    m_num_anchor_refs_list1 = new int[num_views_minus1+1]; // ue(v) 
    m_num_non_anchor_refs_list0 = new int[num_views_minus1+1]; // ue(v)
    m_num_non_anchor_refs_list1 = new int[num_views_minus1+1]; // ue(v)
          
    //JVT-V054
    m_uiViewCodingOrder = new UInt[num_views_minus1+1];

    for (int i=0;i<(int)num_views_minus1+1;i++)
    {
      m_num_anchor_refs_list0[i]=0;
      m_num_anchor_refs_list1[i]=0;
      m_num_non_anchor_refs_list0[i]=0;
      m_num_non_anchor_refs_list1[i]=0;
    }
  }

  Void releaseViewSPSMemory_num_refs_for_lists()
  {
	  
    delete [] m_num_anchor_refs_list0;
    delete [] m_num_anchor_refs_list1;
    delete [] m_num_non_anchor_refs_list0;
    delete [] m_num_non_anchor_refs_list1;
	
    //JVT-V054
    delete [] m_uiViewCodingOrder;
  }


 

  Void initViewSPSMemory_num_level_related_memory(UInt num_level_values_signalled_minus1)
  { 
	m_ui_level_idc = new UInt[num_level_values_signalled_minus1+1];
	m_ui_num_applicable_ops_minus1 = new UInt[num_level_values_signalled_minus1+1];
	m_ui_applicable_op_temporal_id = new UInt*[num_level_values_signalled_minus1+1];
	m_ui_applicable_op_num_target_views_minus1 = new UInt*[num_level_values_signalled_minus1+1];
	m_ui_applicable_op_num_views_minus1 = new UInt*[num_level_values_signalled_minus1+1];
	m_ui_applicable_op_target_view_id = new UInt**[num_level_values_signalled_minus1+1];

    for (int i=0;i<=(int)num_level_values_signalled_minus1;i++)
    {
      m_ui_level_idc[i]=0;
      m_ui_num_applicable_ops_minus1[i]=0;      
    }
  }

  Void releaseViewSPSMemory_num_level_related_memory()
  {
	  
    delete [] m_ui_level_idc;
    delete [] m_ui_num_applicable_ops_minus1;
	delete [] m_ui_applicable_op_temporal_id;
	delete [] m_ui_applicable_op_num_target_views_minus1;
	delete [] m_ui_applicable_op_num_views_minus1; 
	delete [] m_ui_applicable_op_target_view_id; 
    
  }

  Void initViewSPSMemory_num_level_related_memory_2D(UInt num_applicable_ops_minus1,int i)
  {

	  m_ui_applicable_op_temporal_id[i] = new UInt[num_applicable_ops_minus1+1];
	  m_ui_applicable_op_num_target_views_minus1[i] = new UInt[num_applicable_ops_minus1+1];
	  m_ui_applicable_op_num_views_minus1[i] = new UInt[num_applicable_ops_minus1+1];

  }

  Void releaseViewSPSMemory_num_level_related_memory_2D()
  {
	  for (int i=0; i<=this->getNumLevelValuesSignalledMinus1(); i++)
	  {
		delete [] m_ui_applicable_op_temporal_id[i];
		delete [] m_ui_applicable_op_num_target_views_minus1[i];
		delete [] m_ui_applicable_op_num_views_minus1[i];

	  }
  }

  Void initViewSPSMemory_num_level_related_memory_3D(UInt num_applicable_ops_minus1, UInt applicable_op_num_target_views_minus1,int i, int j)
  {

	  
	  m_ui_applicable_op_target_view_id[i] = new UInt*[num_applicable_ops_minus1+1];
	  m_ui_applicable_op_target_view_id[i][j] = new UInt[applicable_op_num_target_views_minus1+1];	
	 

  }

  Void releaseViewSPSMemory_num_level_related_memory_3D()
  {
	  int num_i=this->getNumLevelValuesSignalledMinus1();

	  for (int i=0;i<=num_i; i++) 
	  {
		for (int j=0; j<= (int)this->m_ui_num_applicable_ops_minus1[i]; j++)
	  		delete [] m_ui_applicable_op_target_view_id[i][j];

		delete [] m_ui_applicable_op_target_view_id[i];	
	  }	  

	  
  }



  Void initViewSPSMemory_ref_for_lists(UInt num_views_minus1,int i, int j, int k)
  // i : view-idx, j: list0/1 , k:anchor/non-anchor
  {
    if(!m_bInitDone)
    {
      m_anchor_ref_list0 = new UInt*[num_views_minus1+1];
      m_non_anchor_ref_list0 = new UInt*[num_views_minus1+1];
      m_anchor_ref_list1 = new UInt*[num_views_minus1+1];
      m_non_anchor_ref_list1 = new UInt*[num_views_minus1+1];
      
      for (UInt n = 0; n <= num_views_minus1; n++)
      {
        m_anchor_ref_list0[n] = NULL;
        m_non_anchor_ref_list0[n] = NULL;
        m_anchor_ref_list1[n] = NULL;
        m_non_anchor_ref_list1[n] = NULL;
      }
      m_bInitDone = true;
    }
		 		
    if (j==0) // list0
    {
      if (k==0) // anchor
        m_anchor_ref_list0[i] = new UInt[m_num_anchor_refs_list0[i]];
      else
	    m_non_anchor_ref_list0[i] = new UInt[m_num_non_anchor_refs_list0[i]];
    } 
    else // list1
    {
      if (k==0) // anchor
        m_anchor_ref_list1[i] = new UInt[m_num_anchor_refs_list1[i]];
      else
	    m_non_anchor_ref_list1[i] = new UInt[m_num_non_anchor_refs_list1[i]];
    }		
  }		 
  
  Void releaseViewSPSMemory_ref_for_lists()
  {
	  for (int i=0; i<= this->getNumViewMinus1(); i++)
    {
      if(m_anchor_ref_list0[i])
        delete [] m_anchor_ref_list0[i];

      if(m_anchor_ref_list1[i])
        delete [] m_anchor_ref_list1[i];

      if(m_non_anchor_ref_list0[i])
        delete [] m_non_anchor_ref_list0[i];

      if(m_non_anchor_ref_list1[i])
        delete [] m_non_anchor_ref_list1[i];
    }
    delete [] m_anchor_ref_list0;
    delete [] m_anchor_ref_list1;
    delete [] m_non_anchor_ref_list0;
    delete [] m_non_anchor_ref_list1;
  }
  Void setNumAnchorRefsForListX(int i, int list_no, UInt value) 
  { 
	  AOF(i<= this->m_num_views_minus_1 && i >=0)
      if (list_no==0)
        m_num_anchor_refs_list0[i]=value;
      else if (list_no==1)
        m_num_anchor_refs_list1[i]=value;
  }
  UInt getNumAnchorRefsForListX(int i,int list_no) const
  {
    AOF(i<= this->m_num_views_minus_1 && i >=0)
      if (list_no==0)
        return (UInt)m_num_anchor_refs_list0[i];
    AOF( list_no==1 )
      return (UInt)m_num_anchor_refs_list1[i];
  }
  Void setNumNonAnchorRefsForListX(int i, int list_no, UInt value) 
  { 
    AOF(i<= this->m_num_views_minus_1 && i >=0)
      if (list_no==0)
        m_num_non_anchor_refs_list0[i]=value;
      else if (list_no==1)
        m_num_non_anchor_refs_list1[i]=value;
  }
  UInt getNumNonAnchorRefsForListX(int i,int list_no) const
  {
    AOF(i<= this->m_num_views_minus_1 && i >=0)
      if (list_no==0)
        return (UInt)m_num_non_anchor_refs_list0[i];
    AOF( list_no==1 )
      return (UInt)m_num_non_anchor_refs_list1[i];
  }	

  Void setAnchorRefForListX(int i,int j, int list_no, UInt value)
  {
    AOF(i<= this->m_num_views_minus_1 && i >=0)
		
      if (list_no==0) {
        AOF(j<m_num_anchor_refs_list0[i] && j >=0)		
          m_anchor_ref_list0[i][j] = value;
      }
      else if (list_no==1) {
        AOF(j<m_num_anchor_refs_list1[i] && j >=0)
          m_anchor_ref_list1[i][j] = value;
      }
  }
  UInt getAnchorRefForListX(int i,int j, int list_no) const
  {
    AOF(i<= this->m_num_views_minus_1 && i >=0)
      if (list_no==0){
        AOF(j<m_num_anchor_refs_list0[i] && j >=0)	
          return m_anchor_ref_list0[i][j];
      }
      else if (list_no==1){
        AOF(j<m_num_anchor_refs_list1[i] && j >=0)
          return m_anchor_ref_list1[i][j];
      }
	  else
		  return 0;
  }
  Void setNonAnchorRefForListX(int i,int j, int list_no, UInt value)
  {
	  AOF(i<= this->m_num_views_minus_1 && i >=0)
	  AOF(list_no==0 || list_no==1)
		
      if (list_no==0) {
		  AOF(j<m_num_non_anchor_refs_list0[i] && j >=0)		
          m_non_anchor_ref_list0[i][j] = value;
      }
      else if (list_no==1) {
        AOF(j<m_num_non_anchor_refs_list1[i] && j >=0)
          m_non_anchor_ref_list1[i][j] = value;
      }
  }
  UInt getNonAnchorRefForListX(int i,int j, int list_no) const
  {
    AOF(i<= this->m_num_views_minus_1 && i >=0)
	
      if (list_no==0){
        AOF(j<m_num_non_anchor_refs_list0[i] && j >=0)	
          return m_non_anchor_ref_list0[i][j];
      }
      else if (list_no==1){
        AOF(j<m_num_non_anchor_refs_list1[i] && j >=0)
          return m_non_anchor_ref_list1[i][j];
      } else
		  return 0;
	   
  }

 //JVT-V043 
 UInt getNumRefsForListX(UInt uiCurrViewId,  ListIdx eListIdx, Bool bAnchor) const
 {
   if ( bAnchor )
     return getNumAnchorRefsForListX( uiCurrViewId, eListIdx);
   else
     return getNumNonAnchorRefsForListX (uiCurrViewId, eListIdx);
 }

 UInt getViewIDByViewIndex (UInt uiCurrViewId, UInt uiViewIdx, ListIdx eListIdx, Bool bAnchor)
 {
   if( bAnchor )   
     return getAnchorRefForListX( uiCurrViewId, uiViewIdx, eListIdx);
   else       
     return getNonAnchorRefForListX (uiCurrViewId, uiViewIdx, eListIdx);
 }
 //JVT-V054
 Void setViewCodingOrder(std::string cViewOrder)
 {
   char ch[400];
   char *pch;
   UInt count = 0;
     
   memcpy(ch, cViewOrder.c_str(), cViewOrder.size());
   ch[cViewOrder.size()] = '\0';

   pch = strtok(ch, "-");  
   
   while(pch != NULL)
   {
     m_uiViewCodingOrder[count++] = atoi(pch);     
     pch = strtok(NULL, "-");  
   }
 }
  

  int			m_num_views_minus_1; // ue(v)
  int			*m_num_anchor_refs_list0; // ue(v)
  int			*m_num_anchor_refs_list1; // ue(v)
  int			*m_num_non_anchor_refs_list0; // ue(v)
  int			*m_num_non_anchor_refs_list1; // ue(v)
  UInt			**m_anchor_ref_list0; // u(v)
  UInt			**m_anchor_ref_list1; // u(v)
  UInt			**m_non_anchor_ref_list0; // u(v)
  UInt			**m_non_anchor_ref_list1; // u(v)
  
  //JVT-V054
  UInt                  *m_uiViewCodingOrder;
  Bool                   m_bInitDone;
  int			m_num_level_values_signalled_minus1; // ue(v)
  UInt			*m_ui_level_idc; // u(8)
  UInt			*m_ui_num_applicable_ops_minus1; // ue(v)
  UInt			**m_ui_applicable_op_temporal_id; // u(3)
  UInt			**m_ui_applicable_op_num_target_views_minus1; // ue(v)
  UInt			***m_ui_applicable_op_target_view_id; // ue(v)
  UInt			**m_ui_applicable_op_num_views_minus1; // ue(v)


};





class H264AVCCOMMONLIB_API SequenceParameterSet
{
protected:
  typedef struct
  {
    Bool bValid;
    UInt uiMaxMbPerSec;
    UInt uiMaxFrameSize;
    UInt uiMaxDPBSizeX2;
    UInt uiMaxBitRate;
    UInt uiMaxCPBSize;
    UInt uiMaxVMvRange;
    UInt uiMinComprRatio;
    UInt uiMaxMvsPer2Mb;
  } LevelLimit;

  SequenceParameterSet          ();
  virtual ~SequenceParameterSet ();

public:

  SpsMvcExtension *SpsMVC;
  SpsMvcExtension * getSpsMVC() const {return SpsMVC;};
  static ErrVal create                    ( SequenceParameterSet*& rpcSPS );
  ErrVal        destroy                   ();

  static UInt   getLevelIdc               ( UInt uiMbY, UInt uiMbX, UInt uiOutFreq, UInt uiMvRange, UInt uiNumRefPic );
  UInt          getMaxDPBSize             () const;

  NalUnitType           getNalUnitType                        ()          const { return m_eNalUnitType; }
  UInt                  getLayerId                            ()          const { return m_uiLayerId; }
  Profile               getProfileIdc                         ()          const { return m_eProfileIdc;}
  Bool                  getConstrainedSet0Flag                ()          const { return m_bConstrainedSet0Flag; }
  Bool                  getConstrainedSet1Flag                ()          const { return m_bConstrainedSet1Flag; }
  Bool                  getConstrainedSet2Flag                ()          const { return m_bConstrainedSet2Flag; }
  Bool                  getConstrainedSet3Flag                ()          const { return m_bConstrainedSet3Flag; }
  Bool                  getConstrainedSet4Flag                ()          const { return m_bConstrainedSet4Flag; }
  UInt                  getLevelIdc                           ()          const { return m_uiLevelIdc;}
  UInt                  getSeqParameterSetId                  ()          const { return m_uiSeqParameterSetId;}
  Bool                  getSeqScalingMatrixPresentFlag        ()          const { return m_bSeqScalingMatrixPresentFlag; }
  const ScalingMatrix&  getSeqScalingMatrix                   ()          const { return m_cSeqScalingMatrix; }
  UInt                  getLog2MaxFrameNum                    ()          const { return m_uiLog2MaxFrameNum;}
	UInt                  getPicOrderCntType                    ()          const { return m_uiPicOrderCntType;}
  UInt                  getLog2MaxPicOrderCntLsb              ()          const { return m_uiLog2MaxPicOrderCntLsb;}
  Bool                  getDeltaPicOrderAlwaysZeroFlag        ()          const { return m_bDeltaPicOrderAlwaysZeroFlag;}
  Int                   getOffsetForNonRefPic                 ()          const { return m_iOffsetForNonRefPic;}
  Int                   getOffsetForTopToBottomField          ()          const { return m_iOffsetForTopToBottomField;}
  UInt                  getNumRefFramesInPicOrderCntCycle     ()          const { return m_uiNumRefFramesInPicOrderCntCycle; }
  Int                   getOffsetForRefFrame                  ( UInt ui ) const { return m_aiOffsetForRefFrame[ui]; }
  UInt                  getNumRefFrames                       ()          const { return m_uiNumRefFrames;}
  Bool                  getRequiredFrameNumUpdateBehaviourFlag()          const { return m_bRequiredFrameNumUpdateBehaviourFlag;}
  UInt                  getFrameWidthInMbs                    ()          const { return m_uiFrameWidthInMbs;}
  UInt                  getFrameHeightInMbs                   ()          const { return m_uiFrameHeightInMbs;}
  Bool                  getDirect8x8InferenceFlag             ()          const { return m_bDirect8x8InferenceFlag;}
  UInt                  getMbInFrame                          ()          const { return m_uiFrameWidthInMbs * m_uiFrameHeightInMbs;}
  Bool                  getInitState                          ()          const { return m_bInitDone; }

  Bool getFGSCodingMode                       ()                          const { return m_bFGSCodingMode;   }
  UInt getGroupingSize                        ()                          const { return m_uiGroupingSize;   }
  UInt getPosVect                             ( UInt uiNum )              const { return m_uiPosVect[uiNum]; } 

  Void  setNalUnitType                        ( NalUnitType e )           { m_eNalUnitType                          = e;  }
  Void  setLayerId                            ( UInt        ui )          { m_uiLayerId                             = ui; }
  Void  setProfileIdc                         ( Profile     e  )          { m_eProfileIdc                           = e;  }
  Void  setConstrainedSet0Flag                ( Bool        b  )          { m_bConstrainedSet0Flag                  = b;  }
  Void  setConstrainedSet1Flag                ( Bool        b  )          { m_bConstrainedSet1Flag                  = b;  }
  Void  setConstrainedSet2Flag                ( Bool        b  )          { m_bConstrainedSet2Flag                  = b;  }
  Void  setConstrainedSet3Flag                ( Bool        b  )          { m_bConstrainedSet3Flag                  = b;  }
  Void  setConstrainedSet4Flag                ( Bool        b  )          { m_bConstrainedSet4Flag                  = b;  }
  Void  setLevelIdc                           ( UInt        ui )          { m_uiLevelIdc                            = ui; }
  Void  setSeqParameterSetId                  ( UInt        ui )          { m_uiSeqParameterSetId                   = ui; }
  Void  setSeqScalingMatrixPresentFlag        ( Bool        b  )          { m_bSeqScalingMatrixPresentFlag          = b;  }
  Void  setLog2MaxFrameNum                    ( UInt        ui )          { m_uiLog2MaxFrameNum                     = ui; }
	Void  setPicOrderCntType                    ( UInt        ui )          { m_uiPicOrderCntType                     = ui; }
  Void  setLog2MaxPicOrderCntLsb              ( UInt        ui )          { m_uiLog2MaxPicOrderCntLsb               = ui; }
	Void  setDeltaPicOrderAlwaysZeroFlag        ( Bool        b  )          { m_bDeltaPicOrderAlwaysZeroFlag          = b;  }
  Void  setOffsetForNonRefPic                 ( Int         i  )          { m_iOffsetForNonRefPic                   = i;  }
  Void  setOffsetForTopToBottomField          ( Int         i  )          { m_iOffsetForTopToBottomField            = i;  }
  Void  setNumRefFramesInPicOrderCntCycle     ( UInt        ui )          { m_uiNumRefFramesInPicOrderCntCycle      = ui; }
  Void  setOffsetForRefFrame                  ( UInt        ui, 
                                                Int         i  )          { m_aiOffsetForRefFrame[ui]               = i;  }
  Void  setNumRefFrames                       ( UInt        ui )          { m_uiNumRefFrames                        = ui; }
  Void  setRequiredFrameNumUpdateBehaviourFlag( Bool        b  )          { m_bRequiredFrameNumUpdateBehaviourFlag  = b;  }
  Void  setFrameWidthInMbs                    ( UInt        ui )          { m_uiFrameWidthInMbs                     = ui; }
  Void  setFrameHeightInMbs                   ( UInt        ui )          { m_uiFrameHeightInMbs                    = ui; }
  Void  setDirect8x8InferenceFlag             ( Bool        b  )          { m_bDirect8x8InferenceFlag               = b;  }
  Void  setInitState                          ( Bool        b  )          { m_bInitDone                             = b;  }

  Void setFGSCodingMode                       ( Bool        b  )          { m_bFGSCodingMode                        = b;      }
  Void setGroupingSize                        ( UInt        ui )          { m_uiGroupingSize                        = ui;     }
  Void setPosVect                             ( UInt uiNum, UInt uiVect)  { m_uiPosVect[uiNum]                      = uiVect; } 

  ErrVal write( HeaderSymbolWriteIf*  pcWriteIf )       const;
  ErrVal read ( HeaderSymbolReadIf*   pcReadIf,
                NalUnitType           eNalUnitType );

// TMM_ESS {
  Void setResizeParameters    ( const ResizeParameters * params );
  Void getResizeParameters    ( ResizeParameters * params ) const;

  Void setExtendedSpatialScalability ( UInt ui ) { m_uiExtendedSpatialScalability = ui ;}
  UInt getExtendedSpatialScalability () const    { return m_uiExtendedSpatialScalability; }
// TMM_ESS }

  UInt getCurrentViewId() {return m_uiCurrentViewId;}
  Void setCurrentViewId(UInt ui) {m_uiCurrentViewId = ui;}

protected:
  static ErrVal xGetLevelLimit        ( const LevelLimit*&    rpcLevelLimit,
                                        Int                   iLevelIdc );
  ErrVal        xReadFrext            ( HeaderSymbolReadIf*   pcReadIf );
  ErrVal        xWriteFrext           ( HeaderSymbolWriteIf*  pcWriteIf ) const;


protected:
  Bool          m_bInitDone;

  NalUnitType   m_eNalUnitType;
  UInt          m_uiLayerId;
  Profile       m_eProfileIdc;
  Bool          m_bConstrainedSet0Flag;
  Bool          m_bConstrainedSet1Flag;
  Bool          m_bConstrainedSet2Flag;
  Bool          m_bConstrainedSet3Flag;
  Bool          m_bConstrainedSet4Flag;
  UInt          m_uiLevelIdc;
  UInt          m_uiSeqParameterSetId;
  Bool          m_bSeqScalingMatrixPresentFlag;
  ScalingMatrix m_cSeqScalingMatrix;
  UInt          m_uiLog2MaxFrameNum;
	UInt          m_uiPicOrderCntType;
  UInt          m_uiLog2MaxPicOrderCntLsb;
  Bool          m_bDeltaPicOrderAlwaysZeroFlag;
  Int           m_iOffsetForNonRefPic;
  Int           m_iOffsetForTopToBottomField;
  UInt          m_uiNumRefFramesInPicOrderCntCycle;
  Int           m_aiOffsetForRefFrame[64];
  UInt          m_uiNumRefFrames;
  Bool          m_bRequiredFrameNumUpdateBehaviourFlag;
  UInt          m_uiFrameWidthInMbs;
  UInt          m_uiFrameHeightInMbs;
  Bool          m_bDirect8x8InferenceFlag;

// TMM_ESS {
  UInt          m_uiExtendedSpatialScalability;
  UInt          m_uiChromaPhaseXPlus1;
  UInt          m_uiChromaPhaseYPlus1;
  Int           m_iScaledBaseLeftOffset;
  Int           m_iScaledBaseTopOffset;
  Int           m_iScaledBaseRightOffset;
  Int           m_iScaledBaseBottomOffset;
// TMM_ESS }

// VW {
	UInt					m_auiNumRefIdxUpdateActiveDefault[2];
// VW }

  Bool          m_bFGSCodingMode;
  UInt          m_uiGroupingSize;
  UInt          m_uiPosVect[16];

  UInt          m_uiCurrentViewId;
private:
  static const LevelLimit m_aLevelLimit[52];
};


H264AVC_NAMESPACE_END


#endif // !defined(AFX_SEQUENCEPARAMETERSET_H__66281283_5BFB_429A_B722_6DDE7A11D086__INCLUDED_)
