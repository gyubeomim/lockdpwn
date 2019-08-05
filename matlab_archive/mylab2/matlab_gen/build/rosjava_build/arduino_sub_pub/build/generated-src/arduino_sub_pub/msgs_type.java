package arduino_sub_pub;

public interface msgs_type extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "arduino_sub_pub/msgs_type";
  static final java.lang.String _DEFINITION = "float32 rpm1\nfloat32 rpm2\nfloat32 rpm3\nfloat32 rpm4\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  float getRpm1();
  void setRpm1(float value);
  float getRpm2();
  void setRpm2(float value);
  float getRpm3();
  void setRpm3(float value);
  float getRpm4();
  void setRpm4(float value);
}
