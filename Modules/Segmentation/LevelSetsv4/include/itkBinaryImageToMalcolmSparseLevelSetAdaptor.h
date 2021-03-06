/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef __itkBinaryImageToMalcolmSparseLevelSetAdaptor_h
#define __itkBinaryImageToMalcolmSparseLevelSetAdaptor_h

#include "itkImage.h"
#include "itkLevelSetImageBase.h"
#include "itkMalcolmSparseLevelSetBase.h"
#include "itkImageRegionIteratorWithIndex.h"
#include "itkShapedNeighborhoodIterator.h"
#include "itkNeighborhoodAlgorithm.h"
#include <list>

namespace itk
{
/**
 *  \class BinaryImageToMalcolmSparseLevelSetAdaptor
 *  \brief Base class converting a binary image to a Malcolm level set representation
 *
 *  \tparam TInput Input Image Type
 *  \ingroup ITKLevelSetsv4
 */
template< class TInputImage >
class BinaryImageToMalcolmSparseLevelSetAdaptor : public Object
{
public:
  typedef BinaryImageToMalcolmSparseLevelSetAdaptor   Self;
  typedef SmartPointer< Self >                        Pointer;
  typedef SmartPointer< const Self >                  ConstPointer;
  typedef Object                                      Superclass;

  /** Method for creation through object factory */
  itkNewMacro( Self );

  /** Run-time type information */
  itkTypeMacro( BinaryImageToMalcolmSparseLevelSetAdaptor, Object );

  typedef TInputImage                           InputImageType;
  typedef typename InputImageType::PixelType    InputImagePixelType;
  typedef typename InputImageType::IndexType    InputImageIndexType;
  typedef typename InputImageType::Pointer      InputImagePointer;
  typedef typename InputImageType::RegionType   InputImageRegionType;
  typedef typename NumericTraits< InputImagePixelType >::RealType
                                                InputPixelRealType;

  itkStaticConstMacro ( ImageDimension, unsigned int,
                       InputImageType::ImageDimension );

  typedef MalcolmSparseLevelSetBase< ImageDimension >   LevelSetType;
  typedef typename LevelSetType::Pointer                LevelSetPointer;
  typedef typename LevelSetType::InputType              LevelSetInputType;
  typedef typename LevelSetType::OutputType             LevelSetOutputType;
  typedef typename LevelSetType::OutputRealType         LevelSetOutputRealType;

  typedef typename LevelSetType::LabelObjectType       LevelSetLabelObjectType;
  typedef typename LevelSetLabelObjectType::LabelType  LayerIdType;
  typedef typename LevelSetType::LabelObjectPointer    LevelSetLabelObjectPointer;
  typedef typename LevelSetType::LabelObjectLengthType LevelSetLabelObjectLengthType;
  typedef typename LevelSetType::LabelObjectLineType   LevelSetLabelObjectLineType;

  typedef typename LevelSetType::LabelMapType          LevelSetLabelMapType;
  typedef typename LevelSetType::LabelMapPointer       LevelSetLabelMapPointer;

  typedef typename LevelSetType::LayerType             LevelSetLayerType;
  typedef typename LevelSetType::LayerIterator         LevelSetLayerIterator;
  typedef typename LevelSetType::LayerConstIterator    LevelSetLayerConstIterator;


  /** This is the same as "Procedure 1" as described in
   * "Sparse Field Methods - Technical Report"
   * http://www.shawnlankton.com/2009/04/sfm-and-active-contours/
   *
   * Input is a binary image m_InputImage
   * Output is a label map with 1 as background layer and -1, 0 as foreground layers */
  void Initialize();

  // Set/Get the sparse levet set image
  itkSetObjectMacro( SparseLevelSet, LevelSetType );
  itkGetObjectMacro( SparseLevelSet, LevelSetType );

  // Set get the input image
  itkSetObjectMacro( InputImage, InputImageType );
  itkGetObjectMacro( InputImage, InputImageType );

protected:
  BinaryImageToMalcolmSparseLevelSetAdaptor();
  ~BinaryImageToMalcolmSparseLevelSetAdaptor();

  InputImagePointer       m_InputImage;
  LevelSetPointer         m_SparseLevelSet;
  LevelSetLabelMapPointer m_LabelMap;

  typedef Image< LayerIdType, ImageDimension >  InternalImageType;
  typedef typename InternalImageType::Pointer   InternalImagePointer;

  typedef std::pair< LevelSetInputType, LevelSetOutputType >  LayerPairType;

  InternalImagePointer m_InternalImage;

  typedef ImageRegionIteratorWithIndex< InputImageType >      InputIteratorType;
  typedef ImageRegionIteratorWithIndex< InternalImageType >   InternalIteratorType;

  typedef ShapedNeighborhoodIterator< InternalImageType > NeighborhoodIteratorType;

  /** Find the active layer separating the foreground and background regions */
  void FindActiveLayer();

  /** Ensure that the 0 level set layer is only of single pixel thickness */
  void CreateMinimalInterface();

private:
  BinaryImageToMalcolmSparseLevelSetAdaptor( const Self& ); // purposely not implemented
  void operator = ( const Self& ); // purposely not implemented
};
}
#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBinaryImageToMalcolmSparseLevelSetAdaptor.hxx"
#endif

#endif // __itkBinaryImageToMalcolmSparseLevelSetAdaptor_h
