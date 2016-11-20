#ifndef endlesstunnel_common_hpp
#define endlesstunnel_common_hpp

extern "C" {
    #include <EGL/egl.h>
    #include <GLES2/gl2.h>
    #include <jni.h>
    #include <errno.h>
    #include <android/sensor.h>
    #include <android/log.h>
    #include <unistd.h>
}

//#include "glm/glm.hpp"
//#include "glm/gtc/type_ptr.hpp"
//#include "glm/gtc/matrix_transform.hpp"

#define DEBUG_TAG "100Balls:Native"
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, DEBUG_TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, DEBUG_TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, DEBUG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, DEBUG_TAG, __VA_ARGS__))
#define ABORT_GAME { LOGE("*** GAME ABORTING."); *((char*)0) = 'a'; }
#define DEBUG_BLIP LOGD("[ BLIP ]: %s:%d", __FILE__, __LINE__)

#define ASSERT(cond) { if (!(cond)) { LOGE("ASSERTION FAILED: %s", #cond); \
   ABORT_GAME; } }

#define BUFFER_OFFSET(i) ((char*)NULL + (i))

class LogFunc {
 public:
  LogFunc(const char *_name) {
    name_ = _name;
    LOGD("====>%s", name_);
  }
  ~LogFunc() {
    LOGD("<====%s", name_);
  }
 private:
  const char* name_;
};

//#include "our_key_codes.hpp"

#endif

