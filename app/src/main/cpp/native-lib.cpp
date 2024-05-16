#include <android/log.h> // Incluye esta línea para utilizar la función __android_log_print
#include <jni.h>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>

using namespace cv;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_proyectoo_MainActivity_stringFromJNI(JNIEnv *env, jobject instance, jlong matAddr) {
    cv::Mat& frame = *(cv::Mat*)matAddr;
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        __android_log_print(ANDROID_LOG_ERROR, "Native-Lib", "Cannot open camera");
        return env->NewStringUTF(""); // Devolver una cadena vacía en caso de error
    }

    while (true) {
        cap >> frame;
        if (frame.empty()) {
            __android_log_print(ANDROID_LOG_ERROR, "Native-Lib", "Frame is empty");
            break;
        }

        // Agrega registros para ver los valores de los píxeles en el fotograma (opcional)
        for (int y = 0; y < frame.rows; y++) {
            for (int x = 0; x < frame.cols; x++) {
                Vec3b color = frame.at<Vec3b>(y, x);
                __android_log_print(ANDROID_LOG_DEBUG, "Native-Lib", "Pixel at (%d, %d): (%d, %d, %d)", x, y, color[0], color[1], color[2]);
            }
        }
    }
    cap.release();

    return env->NewStringUTF("");
}
