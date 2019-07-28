#include <iostream>

using namespace std;

class FeatureExtractor {
 public:
  virtual void computeKeypoint()=0;
};

class FeatureDescriptor {
 public:
  virtual void computeDescription()=0;
};

class SIFTextractor : public FeatureExtractor {
 public:
  virtual void computeKeypoint() {
    cout << "SIFTextractor called!" << endl;
  }
};

class ORBextractor : public FeatureExtractor {
 public:
  virtual void computeKeypoint() {
    cout << "ORBextractor called!" << endl;
  }
};

class BRIEFdescriptor : public FeatureDescriptor {
 public:
  virtual void computeDescription() {
    cout << "BRIEFdescriptor called!" << endl;
  }
};

class ORBdescriptor : public FeatureDescriptor {
 public:
  virtual void computeDescription() {
    cout << "ORBdescriptor called!" << endl;
  }
};

class Feature { // original class: ORBextractor.cc
 public:
  Feature() {
    pExtractor = new SIFTextractor;
    pDescriptor = new BRIEFdescriptor;
  }

  virtual void operator()() {
    pExtractor->computeKeypoint();
    pDescriptor->computeDescription();
  }

  FeatureExtractor* pExtractor;
  FeatureDescriptor* pDescriptor;
};


int main() {
  Feature* feature = new Feature();

  (*feature)();

  return 0;
}
