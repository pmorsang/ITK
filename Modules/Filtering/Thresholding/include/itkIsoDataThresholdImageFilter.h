
#ifndef __itkIsoDataThresholdImageFilter_h
#define __itkIsoDataThresholdImageFilter_h

#include "itkImageToImageFilter.h"
#include "itkFixedArray.h"

namespace itk {

/** \class IsoDataThresholdImageFilter
 * \brief Threshold an image using the IsoData Threshold
 *
 * This filter creates a binary thresholded image that separates an
 * image into foreground and background components. The filter
 * computes the threshold using the IsoDataThresholdCalculator and
 * applies that theshold to the input image using the
 * BinaryThresholdImageFilter.
 *
 * \sa BinaryThresholdImageFilter
 * \ingroup IntensityImageFilters  Multithreaded
 */

template<class TInputImage, class TOutputImage>
class ITK_EXPORT IsoDataThresholdImageFilter :
    public ImageToImageFilter<TInputImage, TOutputImage>
{
public:
  /** Standard Self typedef */
  typedef IsoDataThresholdImageFilter                      Self;
  typedef ImageToImageFilter<TInputImage,TOutputImage>     Superclass;
  typedef SmartPointer<Self>                               Pointer;
  typedef SmartPointer<const Self>                         ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Runtime information support. */
  itkTypeMacro(IsoDataThresholdImageFilter, ImageToImageFilter);

  typedef TInputImage                       InputImageType;
  typedef TOutputImage                      OutputImageType;

  /** Image pixel value typedef. */
  typedef typename InputImageType::PixelType   InputPixelType;
  typedef typename OutputImageType::PixelType  OutputPixelType;

  /** Image related typedefs. */
  typedef typename InputImageType::Pointer  InputImagePointer;
  typedef typename OutputImageType::Pointer OutputImagePointer;

  typedef typename InputImageType::SizeType    InputSizeType;
  typedef typename InputImageType::IndexType   InputIndexType;
  typedef typename InputImageType::RegionType  InputImageRegionType;
  typedef typename OutputImageType::SizeType   OutputSizeType;
  typedef typename OutputImageType::IndexType  OutputIndexType;
  typedef typename OutputImageType::RegionType OutputImageRegionType;


  /** Image related typedefs. */
  itkStaticConstMacro(InputImageDimension, unsigned int,
                      InputImageType::ImageDimension );
  itkStaticConstMacro(OutputImageDimension, unsigned int,
                      OutputImageType::ImageDimension );

  /** Set the "outside" pixel value. The default value
   * NumericTraits<OutputPixelType>::Zero. */
  itkSetMacro(OutsideValue,OutputPixelType);

  /** Get the "outside" pixel value. */
  itkGetConstMacro(OutsideValue,OutputPixelType);

  /** Set the "inside" pixel value. The default value
   * NumericTraits<OutputPixelType>::max() */
  itkSetMacro(InsideValue,OutputPixelType);

  /** Get the "inside" pixel value. */
  itkGetConstMacro(InsideValue,OutputPixelType);

  /** Get the computed threshold. */
  itkGetConstMacro(Threshold,InputPixelType);


#ifdef ITK_USE_CONCEPT_CHECKING
  /** Begin concept checking */
  itkConceptMacro(OutputEqualityComparableCheck,
    (Concept::EqualityComparable<OutputPixelType>));
  itkConceptMacro(InputOStreamWritableCheck,
    (Concept::OStreamWritable<InputPixelType>));
  itkConceptMacro(OutputOStreamWritableCheck,
    (Concept::OStreamWritable<OutputPixelType>));
  /** End concept checking */
#endif
protected:
  IsoDataThresholdImageFilter();
  ~IsoDataThresholdImageFilter(){};
  void PrintSelf(std::ostream& os, Indent indent) const;

  void GenerateInputRequestedRegion();
  void GenerateData ();

private:
  IsoDataThresholdImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  InputPixelType      m_Threshold;
  OutputPixelType     m_InsideValue;
  OutputPixelType     m_OutsideValue;

}; // end of class

} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkIsoDataThresholdImageFilter.hxx"
#endif

#endif
