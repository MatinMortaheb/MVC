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




#if !defined(AFX_FRAMEUNIT_H__F112E873_18DC_48C6_9E5E_A46FF23388E3__INCLUDED_)
#define AFX_FRAMEUNIT_H__F112E873_18DC_48C6_9E5E_A46FF23388E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "H264AVCCommonLib/MbDataCtrl.h"
#include "H264AVCCommonLib/Frame.h"
#include "H264AVCCommonLib/IntFrame.h"

enum MultiviewReferenceDirection { NOT_MULTIVIEW=0, FORWARD, BACKWARD };

H264AVC_NAMESPACE_BEGIN



class H264AVCCOMMONLIB_API FrameUnit
{
    enum
    {
#ifdef   LF_INTERLACE
        TOP_FLD_SHORT = 0x01,
        BOT_FLD_SHORT = 0x02,
        FRAME_SHORT   = 0x03,
        TOP_FLD_LONG  = 0x04,
        BOT_FLD_LONG  = 0x08,
        FRAME_LONG    = 0x0c,
        TOP_FLD_REF   = 0x05,
        BOT_FLD_REF   = 0x0a,
        FRAME_REF     = 0x0f,
        IS_OUTPUTTED  = 0x10,
#else //!LF_INTERLACE
        REFERENCE     = 0x01,
        IS_OUTPUTTED  = 0x02,
#endif //LF_INTERLACE
    };

protected:
    FrameUnit( YuvBufferCtrl& rcYuvFullPelBufferCtrl, YuvBufferCtrl& rcYuvHalfPelBufferCtrl, Bool 

        bOriginal );
    virtual ~FrameUnit();

public:
    ErrVal init( const SliceHeader& rcSH, PicBuffer *pcPicBuffer );
    ErrVal init( const SliceHeader& rcSH, FrameUnit& rcFrameUnit ); // HS: decoder robustness
    ErrVal copyBase( const SliceHeader& rcSH, FrameUnit& rcFrameUnit ); //JVT-S036 lsj
    ErrVal uninit();
    ErrVal uninitBase();

    static ErrVal create( FrameUnit*& rpcFrameUnit, YuvBufferCtrl& rcYuvFullPelBufferCtrl, YuvBufferCtrl& rcYuvHalfPelBufferCtrl, Bool bOriginal = false );
    ErrVal destroy ();

    Frame& getFrame()                             { return m_cFrame;    }
#ifdef   LF_INTERLACE
    Frame& getTopField()                          { return m_cTopField; }
    Frame& getBotField()                          { return m_cBotField; }
#endif //LF_INTERLACE
    const Frame& getFrame()                 const { return m_cFrame;    }
#ifdef   LF_INTERLACE
    const Frame& getTopField()              const { return m_cTopField; }
    const Frame& getBotField()              const { return m_cBotField; }
	const Frame& getFrame(PicType ePicType) const { return ePicType==FRAME?m_cFrame:(ePicType==TOP_FIELD?m_cTopField:m_cBotField);}

    RefPic getRefPic( PicType ePicType, const RefPic& rcRefPic ) const;
    Frame& getPic( PicType ePicType )             { return ( ePicType == FRAME ) ? m_cFrame : ( ePicType 

        == BOT_FIELD ) ? m_cBotField : m_cTopField; }
    const Frame& getPic( PicType ePicType ) const { return ( ePicType == FRAME ) ? m_cFrame : ( ePicType 

        == BOT_FIELD ) ? m_cBotField : m_cTopField; }
#endif //LF_INTERLACE

    Void  setFrameNumber( UInt  uiFN )            { m_uiFrameNumber = uiFN; }
    UInt  getFrameNumber()                  const { return m_uiFrameNumber; }

    Void  setBaseRep    ( Bool  bFlag )			{ m_BaseRepresentation = bFlag; } //JVT-S036 
    UInt  getBaseRep	  ()				  const { return m_BaseRepresentation;  } //JVT-S036 
    UChar getStatus	  ()				  const { return m_uiStatus;}

    Void  setOutputDone ()                        { m_uiStatus |= IS_OUTPUTTED; }
    Bool  isOutputDone  ()                  const { return ( m_uiStatus & IS_OUTPUTTED ? true : false ); 

    }

#ifdef   LF_INTERLACE
    Bool  isRefPic      ()                  const { return ( m_uiStatus & 0xf ? true : false ); }
    Bool  isShortTerm   ( PicType ePicType )const { return ePicType == (m_uiStatus &  ePicType); }
    Bool  isUsed        ( PicType ePicType )const { return ( m_uiStatus & ( ePicType + ( ePicType 

        << 2) ) ? true : false ); }
    Void  setShortTerm  ( PicType ePicType )      { m_uiStatus |= ePicType; m_uiStatus &= ~( 

        ePicType << 2); }
    Bool  isSecField()                      const  { return 0 != m_eAvailable;  }
    Bool  isBothFields()                    const  { return FRAME == m_eAvailable; }
    Bool  isValid       ( UChar ucPicType ) const
    {
        return (((m_uiStatus & ucPicType) == ucPicType) || ( ((m_uiStatus>>2) & ucPicType) == ucPicType) );
    }
    Void  setUnused     ( PicType ePicType );
#else //!LF_INTERLACE
    Bool  isUsed        ()                  const { return ( m_uiStatus & REFERENCE ? true : false ); }
    Void  setUsed       ()                        { m_uiStatus |= REFERENCE; }
    Void  setUnused     ();
#endif //LF_INTERLACE
    Int   getMaxPOC     ()                  const { return m_iMaxPOC; }
#ifdef   LF_INTERLACE
    Void  setTopFieldPoc( Int iPoc );
    Void  setBotFieldPoc( Int iPoc );
    PicType getAvailableStatus()            const { return m_eAvailable; }
    Void setPicStruct( PicStruct ePicStruct )     { m_ePicStruct = ePicStruct; }
    PicStruct getPicStruct()                const { return m_ePicStruct; }
    Bool isFieldCoded()                     const { return m_bFieldCoded; }
    Void addPic( PicType ePicType, Bool bFieldCoded = false, UInt uiIdrPicId = 0 );
#else //!LF_INTERLACE
    Void setPoc( Int iPoc );
#endif //LF_INTERLACE

    PicBuffer*  getPicBuffer  ()            const { return m_pcPicBuffer; }
    const MbDataCtrl* getMbDataCtrl()       const { return &m_cMbDataCtrl; }
    MbDataCtrl* getMbDataCtrl()                   { return &m_cMbDataCtrl;  }
#ifdef   LF_INTERLACE
    const IntFrame* getResidual()           const { return &m_cResidual; }
    IntFrame* getResidual()                       { return &m_cResidual; }
#endif
private:
    Frame         m_cFrame;
#ifdef   LF_INTERLACE
    Frame         m_cTopField;
    Frame         m_cBotField;
    PicType       m_eAvailable;
    PicStruct     m_ePicStruct;
    Bool          m_bFieldCoded;
	IntFrame      m_cResidual;
#endif //LF_INTERLACE
    MbDataCtrl    m_cMbDataCtrl;
    PicBuffer*    m_pcPicBuffer;
    UInt          m_uiFrameNumber;
    UChar         m_uiStatus;
    Int           m_iMaxPOC;
    Bool          m_bOriginal;
    Bool          m_bInitDone;
   // IntFrame      m_cResidual;
    Bool			m_BaseRepresentation; //JVT-S036
    Bool          m_bConstrainedIntraPred;

    UInt          m_uiFGSReconCount;
    //MultiviewReferenceDirection     m_multiviewRefDirection;
    };



    H264AVC_NAMESPACE_END


#endif // !defined(AFX_FRAMEUNIT_H__F112E873_18DC_48C6_9E5E_A46FF23388E3__INCLUDED_)
