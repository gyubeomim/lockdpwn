#include "FlyCapture2.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace FlyCapture2;
using namespace std;

void PrintError(Error error) {
  error.PrintErrorTrace();
}

void PrintBuildInfo() {
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

void PrintCameraInfo(CameraInfo *pCamInfo) {
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

bool SetProperty(Camera& camera, const FlyCapture2::PropertyType &type, const bool &autoSet, double value) {
  // return true if we can set values as desired.
  bool retVal = true;

  PropertyInfo pInfo;
  pInfo.type = type;
  Error error = camera.GetPropertyInfo(&pInfo);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  if(pInfo.present)
  {
    Property prop;
    prop.type = type;
    prop.autoManualMode = (autoSet && pInfo.autoSupported);
    prop.absControl = pInfo.absValSupported;
    prop.onOff = pInfo.onOffSupported;

    if(value < pInfo.absMin)
    {
      value = pInfo.absMin;
      retVal &= false;
    }
    else if(value > pInfo.absMax)
    {
      value = pInfo.absMax;
      retVal &= false;
    }
    prop.absValue = value;
    error = camera.SetProperty(&prop);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

    // Read back setting to confirm
    error = camera.GetProperty(&prop);
    if (error != PGRERROR_OK) {
      PrintError(error);
      return -1;
    }
    if(!prop.autoManualMode)
    {
      value = prop.absValue;
    }
  }
  else     // Not supported
  {
    value = 0.0;
  }
  return retVal;
}
int RunSingleCamera(PGRGuid guid) {
  const int k_num_images = 600;

  Error error;

  // Connect to a camera
  Camera camera;
  error = camera.Connect(&guid);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  // Get the camera information
  CameraInfo camera_info;
  error = camera.GetCameraInfo(&camera_info);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  PrintCameraInfo(&camera_info);

  SetProperty(camera, FlyCapture2::FRAME_RATE, false, 30.);

  // // Turn Timestamp on
  EmbeddedImageInfo image_info;
  image_info.timestamp.onOff = true;
  // image_info.exposure.onOff = true;
  // image_info.shutter.onOff = true;
  error = camera.SetEmbeddedImageInfo(&image_info);
  if (error != PGRERROR_OK) {
    PrintError(error);
    cout << "Press Enter to exit." << endl;
    cin.ignore();
    return -1;
  }

  // Get the camera configuration
  FC2Config config;
  error = camera.GetConfiguration(&config);
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  // Set the number of driver buffers used to 10.
  config.numBuffers = 10;

  // Set the camera configuration
  error = camera.SetConfiguration(&config);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }
  // Start capturing images
  error = camera.StartCapture();
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  Property prop;
  prop.type = FlyCapture2::SHUTTER;
  error = camera.GetProperty(&prop);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  stringstream ss;
  ofstream fout_time("times.txt");
  ostringstream fout_img;

  Image rawImage;
  for (int image_count = 0; image_count < k_num_images; image_count++) {
    // Retrieve an image
    error = camera.RetrieveBuffer(&rawImage);
    if (error != PGRERROR_OK) {
      PrintError(error);
      continue;
    }

    cout << "Grabbed image " << image_count << endl;

    // Create a converted image
    Image converted_image;

    // Convert the raw image
    error = rawImage.Convert(PIXEL_FORMAT_MONO8, &converted_image);

    if (error != PGRERROR_OK) {
      PrintError(error);
      return -1;
    }
    // get shutter speed (= exposure speed)
    error = camera.GetProperty(&prop);
    std::cout << prop.absValue << std::endl;

    // Set header timestamp as embedded for now
    TimeStamp embeddedTime = rawImage.GetTimeStamp();
    int time = embeddedTime.seconds;
    int ntime = 1000 * embeddedTime.microSeconds;

    ss.str("");
    ss << std::to_string(image_count) << " " << std::to_string(time) << "." << std::to_string(ntime) << " " << prop.absValue / 1000. << std::endl;

    // save timestamps into times.txt
    fout_time<< ss.str();

    // Create a unique fout_img
    fout_img.str("");
    fout_img << "000" << image_count << ".png";

    // Save the image. If a file format is not passed in, then the file
    // extension is parsed to attempt to determine the file format.
    error = converted_image.Save(fout_img.str().c_str());
    if (error != PGRERROR_OK) {
      PrintError(error);
      return -1;
    }
  }

  // Stop capturing images
  error = camera.StopCapture();
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  // Disconnect the camera
  error = camera.Disconnect();
  if (error != PGRERROR_OK)
  {
    PrintError(error);
    return -1;
  }

  return 0;
}

int main(int argc, char **argv) {
  PrintBuildInfo();

  Error error;

  BusManager bus_manager;
  unsigned int num_cameras;
  error = bus_manager.GetNumOfCameras(&num_cameras);
  if (error != PGRERROR_OK) {
    PrintError(error);
    return -1;
  }

  cout << "Number of cameras detected: " << num_cameras << endl;

  for (unsigned int i = 0; i < num_cameras; i++) {
    PGRGuid guid;
    error = bus_manager.GetCameraFromIndex(i, &guid);
    if (error != PGRERROR_OK) {
      PrintError(error);
      return -1;
    }

    RunSingleCamera(guid);
  }

  cout << "Press Enter to exit..." << endl;
  cin.ignore();

  return 0;
}
