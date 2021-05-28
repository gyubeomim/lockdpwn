# Stereo-Reconstruction
This repository consists of the implementation of Stereo Reconstruction in MATLAB.

## Overview

Given two images of the same subject clicked from a slightly different angle, this code computes the depth of the objects in the image. The code works as described below:

- SIFT Feature Matching: 
Using the Scale Invariant Feature Transform (SIFT), extract the keypoints in the two images and match them using KNN search. Perform ratio test and bi-directional consistency check to discard the inappropriate matches.

- Fundamental Matrix Computation: 
Using the matched keypoints, compute the Fundamental Matrix to draw epipolar lines and locate the epipole. Fundamental Matrix is robustly computed by the 8-point algorithm within RANSAC. Perform SVD clean-up. Given the fundamental matrix, compute the four sets of possible camera pose.

- Triangulation: 
Given the camera pose and correspondences, perform triangulation to reconstruct 3D points.

- Pose Disambiguation: 
Given four configurations of relative camera pose, find the best camera pose by verifying through 3D point triangulation; the 3D point must lie in front of both the cameras.

- Stereo: 
Given the disambiguated camera pose, find the dense stereo matching between two views based on Dense SIFT. Find the rectification rotation matrix and homography, which aligns the x-axis of the images with the baseline and sends the epipole to infinity where the epipolar lines become horizontal. Finally, get the disparity map by searching for the best Dense SIFT matches along the epipolar line of a particular pixel.
