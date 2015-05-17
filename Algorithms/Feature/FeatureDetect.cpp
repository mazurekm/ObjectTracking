#include "FeatureDetect.h"


#include <opencv2/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <opencv2/xfeatures2d.hpp>


#include <FrameProcessing/ImageMarker.h>

#include<algorithm>
#include<vector>
#include<functional>

using namespace cv;
using namespace cv::xfeatures2d;

CFeatureDetect::CFeatureDetect(const CTransformContainer &container, const std::string &winName) : CAbstractAlgorithm(container, winName)
{

}

CFeatureDetect::CFeatureDetect(const std::string &winName) : CAbstractAlgorithm(winName)
{
}

void CFeatureDetect::perform(CVideoLoader &loader)
{
	int minHessian = 400;
	cv:: Mat frame;

	cv::namedWindow(m_winName, cv::WINDOW_AUTOSIZE );

	Ptr<SURF> detector = SURF::create( minHessian );
	CImageMarker::getInstance().setWinName(m_winName);


	while(true)
	{
		
		if(false == CImageMarker::getInstance().isMarkerActive()) 
		{
			frame = loader.getNextFrame();
            CImageMarker::getInstance().setFrame( frame );

			auto imgVec = CImageMarker::getInstance().getImgVec();
		
			
			for(auto iter = imgVec.begin(); iter != imgVec.end(); ++iter)
			{
				std::vector<cv::KeyPoint> keypoints_object, keypoints_scene;
				cv::Mat descriptors_object, descriptors_scene;
			
				detector->detectAndCompute( iter->second, noArray(), keypoints_object, descriptors_object );
  				detector->detectAndCompute( frame, noArray(), keypoints_scene, descriptors_scene ); 
				
				cv::FlannBasedMatcher matcher;
				std::vector< cv::DMatch > matches;
				matcher.match( descriptors_object, descriptors_scene, matches );

				auto predicate = [](DMatch i, DMatch j) { return i.distance < j.distance;}; 

				auto minElIter = std::min_element(matches.begin(), matches.end(), predicate);
			
				double min = 100;	
				if(matches.end() != minElIter)
				{
					min = minElIter->distance;
				}
			
				std::vector< DMatch > good_matches;
			
				auto cond =  [&min](DMatch el) {return el.distance <= std::max(2*min, 0.02);};
				std::copy_if(matches.begin(), matches.end(), std::back_inserter(good_matches), cond);

				Mat img_matches;
				if(false == good_matches.empty())
				{
		  			drawMatches( iter->second, keypoints_object, frame, keypoints_scene,
					                 good_matches, img_matches, Scalar::all(-1), Scalar::all(-1),
							                  std::vector<char>(), 2 );	
					frame = img_matches.clone();
				}
			}	

			cv::imshow(m_winName, frame);
        }
		else
		{
            cv::imshow(m_winName, CImageMarker::getInstance().getFrame() );
		}	

		if(cv::waitKey(20) == 1048603)
		{
			break;
		}	
	}
}

