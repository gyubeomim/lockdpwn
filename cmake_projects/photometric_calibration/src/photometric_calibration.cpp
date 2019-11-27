#include "FlyCapture2.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace FlyCapture2;
using namespace std;

void PrintBuildInfo()
{
  FC2Version fc2Version;
  Utilities::GetLibraryVersion(&fc2Version);

  ostringstream version;
  version << "FlyCapture2 library version: " << fc2Version.major << "."
          << fc2Version.minor << "." << fc2Version.type << "."
          << fc2Version.build;
  cout << version.str() << endl;

  ostringstream timeStamp;
  timeStamp << "Application build date: " << __DATE__ << " " << __TIME__;
  cout << timeStamp.str() << endl << endl;
}

void PrintCameraInfo(CameraInfo *pCamInfo)
{
  cout << endl;
  cout << "*** CAMERA INFORMATION ***" << endl;
  cout << "Serial number - " << pCamInfo->serialNumber << endl;
  cout << "Camera model - " << pCamInfo->modelName << endl;
  cout << "Camera vendor - " << pCamInfo->vendorName << endl;
  cout << "Sensor - " << pCamInfo->sensorInfo << endl;
  cout << "Resolution - " << pCamInfo->sensorResolution << endl;
  cout << "Firmware version - " << pCamInfo->firmwareVersion << endl;
  cout << "Firmware build time - " << pCamInfo->firmwareBuildTime << endl
       << endl;
}

void PrintError(Error error) { error.PrintErrorTrace(); }

int RunSingleCamera(PGRGuid guid) {
  const int k_num_images = 100;

  Error error;

  // Connect to a camera
  Camera cam;
  error = cam.Connect(&guid);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  // Get the camera information
  CameraInfo camInfo;
  error = cam.GetCameraInfo(&camInfo);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  PrintCameraInfo(&camInfo);

  // // Turn Timestamp on
  EmbeddedImageInfo imageInfo;
  imageInfo.timestamp.onOff = true;
  imageInfo.exposure.onOff = true;
  imageInfo.shutter.onOff = true;
  error = cam.SetEmbeddedImageInfo(&imageInfo);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    cout << "Press Enter to exit." << endl;
    cin.ignore();
    return -1;
  }

  // Get the camera configuration
  FC2Config config;
  error = cam.GetConfiguration(&config);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  // Set the number of driver buffers used to 10.
  config.numBuffers = 10;

  // Set the camera configuration
  error = cam.SetConfiguration(&config);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }
  // Start capturing images
  error = cam.StartCapture();
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  Property prop;
  prop.type = FlyCapture2::SHUTTER;
  error = cam.GetProperty(&prop);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  stringstream ss;
  ofstream fout("times.txt");

  Image rawImage;
  for (int imageCnt = 0; imageCnt < k_num_images; imageCnt++) {
    // Retrieve an image
    error = cam.RetrieveBuffer(&rawImage);
    if (error != PGRERROR_OK)
    {
      PrintError(error);
      continue;
    }

    cout << "Grabbed image " << imageCnt << endl;

    // Create a converted image
    Image convertedImage;

    // Convert the raw image
    error = rawImage.Convert(PIXEL_FORMAT_MONO8, &convertedImage);
    if (error != PGRERROR_OK)
    {
      PrintError(error);
      return -1;
    }
    // get shutter speed (= exposure speed)
    error = cam.GetProperty(&prop);
    std::cout << prop.absValue << std::endl;

    // Set header timestamp as embedded for now
    TimeStamp embeddedTime = rawImage.GetTimeStamp();
    int time = embeddedTime.seconds;
    int ntime = 1000 * embeddedTime.microSeconds;

    ss.str("");
    ss << std::to_string(imageCnt) << " " << std::to_string(time) << "." << std::to_string(ntime) << " " << prop.absValue / 1000. << std::endl;
    fout<< ss.str();

    // Create a unique filename
    ostringstream filename;
    filename << "photometric_calibration-" << camInfo.serialNumber << "-"
             << imageCnt << ".png";

    // Save the image. If a file format is not passed in, then the file
    // extension is parsed to attempt to determine the file format.
    error = convertedImage.Save(filename.str().c_str());
    if (error != PGRERROR_OK)
    {
      PrintError(error);
      return -1;
    }
  }

  // Stop capturing images
  error = cam.StopCapture();
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  // Disconnect the camera
  error = cam.Disconnect();
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  return 0;
}

int main(int /*argc*/, char ** /*argv*/)
{
  PrintBuildInfo();

  Error error;

  // Since this application saves images in the current folder
  // we must ensure that we have permission to write to this folder.
  // If we do not have permission, fail right away.
  FILE *tempFile = fopen("test.txt", "w+");
  if (tempFile == NULL)
  {
    cout << "Failed to create file in current folder.  Please check "
        "permissions."
         << endl;
    return -1;
  }
  fclose(tempFile);
  remove("test.txt");

  BusManager busMgr;
  unsigned int numCameras;
  error = busMgr.GetNumOfCameras(&numCameras);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  cout << "Number of cameras detected: " << numCameras << endl;

  for (unsigned int i = 0; i < numCameras; i++)
  {
    PGRGuid guid;
    error = busMgr.GetCameraFromIndex(i, &guid);
    if (error != PGRERROR_OK)
    {
      PrintError(error);
      return -1;
    }

    RunSingleCamera(guid);
  }

  cout << "Press Enter to exit..." << endl;
  cin.ignore();

  return 0;
}
