/*
 * Copyright 2020-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license.
 */

#include <map>
#include "jni_JniMath.h"
#include "mk_math.h"

#define SCALAR_FUNCTION_HOMOGEN_WITH_TYPE(fun, varr) \
        switch (type) {\
            case 1: {\
                auto *arr = (int8_t *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }\
            case 2: {\
                auto *arr = (int16_t *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }\
            case 3: {\
                auto *arr = (int32_t *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }\
            case 4: {\
                auto *arr = (int64_t *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }\
            case 5: {\
                auto *arr = (float *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }\
            case 6: {\
                auto *arr = (double *)(varr);\
                arg = fun(arr, offset, size);\
                break;\
            }                            \
            default:break;\
        }                                            \

#define SCALAR_FUNCTION_WITH_TYPE(fun, varr) \
        switch (type) {\
            case 1: {\
                auto *arr = reinterpret_cast<int8_t *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }\
            case 2: {\
                auto *arr = reinterpret_cast<int16_t *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }\
            case 3: {\
                auto *arr = reinterpret_cast<int32_t *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }\
            case 4: {\
                auto *arr = reinterpret_cast<int64_t *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }\
            case 5: {\
                auto *arr = reinterpret_cast<float *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }\
            case 6: {\
                auto *arr = reinterpret_cast<double *>(varr);\
                arg = fun(arr, offset, size, dim, shape, strides);\
                break;\
            }                            \
            default:break;\
        }                                    \


template<typename T>
jobject getNewJObject(JNIEnv *env, T value, const char *class_name, const char *jtype) {
  jobject ret;
  jclass cls = env->FindClass(class_name);
  jmethodID init = env->GetMethodID(cls, "<init>", jtype);
  if (nullptr == init) return nullptr;
  ret = env->NewObject(cls, init, value);
  return ret;
}


/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    argMax
 * Signature: (Ljava/lang/Object;II[I[II)I
 */
JNIEXPORT jint JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_argMax
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size, jintArray jshape, jintArray jstrides, jint type) {
  int arg = 0;
  int dim;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }

  void *varr = env->GetPrimitiveArrayCritical((jarray)jarr, nullptr);

  if (strides == nullptr) {
	SCALAR_FUNCTION_HOMOGEN_WITH_TYPE(array_argmax, varr)
  } else {
	SCALAR_FUNCTION_WITH_TYPE(array_argmax, varr)
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, varr, 0);

  return arg;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    argMin
 * Signature: (Ljava/lang/Object;II[I[II)I
 */
JNIEXPORT jint JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_argMin
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size, jintArray jshape, jintArray jstrides, jint type) {
  int arg = 0;
  int dim;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }
  void *varr = env->GetPrimitiveArrayCritical((jarray)jarr, nullptr);

  if (strides == nullptr) {
	SCALAR_FUNCTION_HOMOGEN_WITH_TYPE(array_argmin, varr)
  } else {
	SCALAR_FUNCTION_WITH_TYPE(array_argmin, varr)
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, varr, 0);

  return arg;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    exp
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_exp___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_exp(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    exp
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_exp___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_exp(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    expC
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_expC___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_exp_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    expC
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_expC___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_exp_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    log
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_log___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_log(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    log
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_log___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_log(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    logC
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_logC___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_log_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    logC
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_logC___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_log_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    sin
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_sin___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_sin(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    sin
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_sin___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_sin(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    sinC
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_sinC___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_sin_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    sinC
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_sinC___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_sin_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    cos
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_cos___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_cos(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    cos
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_cos___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_cos(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    cosC
 * Signature: ([FI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_cosC___3FI
	(JNIEnv *env, jobject jobj, jfloatArray j_arr, jint size) {
  auto arr = (float *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_cos_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    cosC
 * Signature: ([DI)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_cosC___3DI
	(JNIEnv *env, jobject jobj, jdoubleArray j_arr, jint size) {
  auto arr = (double *)(env->GetPrimitiveArrayCritical(j_arr, nullptr));
  array_cos_complex(arr, size);
  env->ReleasePrimitiveArrayCritical(j_arr, arr, 0);
  return true;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    max
 * Signature: (Ljava/lang/Object;II[I[II)Ljava/lang/Number;
 */
JNIEXPORT jobject JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_max
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size, jintArray jshape, jintArray jstrides, jint type) {
  int dim;
  jobject ret = nullptr;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }
  void *varr = env->GetPrimitiveArrayCritical((jarray)jarr, nullptr);

  switch (type) {
	case 1: {
	  auto *arr = (int8_t *)(varr);
	  int8_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Byte", "(B)V");
	  break;
	}
	case 2: {
	  auto *arr = (int16_t *)(varr);
	  int16_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Short", "(S)V");
	  break;
	}
	case 3: {
	  auto *arr = (int32_t *)(env->GetPrimitiveArrayCritical((jarray)jarr, nullptr));
	  int32_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Integer", "(I)V");
	  break;
	}
	case 4: {
	  auto *arr = (int64_t *)(env->GetPrimitiveArrayCritical((jarray)jarr, nullptr));
	  int64_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Long", "(J)V");
	  break;
	}
	case 5: {
	  auto *arr = (float *)(env->GetPrimitiveArrayCritical((jarray)jarr, nullptr));
	  float_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Float", "(F)V");
	  break;
	}
	case 6: {
	  auto *arr = (double *)(env->GetPrimitiveArrayCritical((jarray)jarr, nullptr));
	  double_t
		  tmp = (strides != nullptr) ? array_max(arr, offset, size, dim, shape, strides) : array_max(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Double", "(D)V");
	  break;
	}
	default:break;
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, varr, 0);

  return ret;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    min
 * Signature: (Ljava/lang/Object;II[I[II)Ljava/lang/Number;
 */
JNIEXPORT jobject JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_min
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size, jintArray jshape, jintArray jstrides, jint type) {
  int dim;
  jobject ret = nullptr;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }
  void *varr = env->GetPrimitiveArrayCritical((jarray)jarr, nullptr);

  switch (type) {
	case 1: {
	  auto *arr = (int8_t *)(varr);
	  int8_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Byte", "(B)V");
	  break;
	}
	case 2: {
	  auto *arr = (int16_t *)(varr);
	  int16_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Short", "(S)V");
	  break;
	}
	case 3: {
	  auto *arr = (int32_t *)(varr);
	  int32_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Integer", "(I)V");
	  break;
	}
	case 4: {
	  auto *arr = (int64_t *)(varr);
	  int64_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Long", "(J)V");
	  break;
	}
	case 5: {
	  auto *arr = (float *)(varr);
	  float_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Float", "(F)V");
	  break;
	}
	case 6: {
	  auto *arr = (double *)(varr);
	  double_t
		  tmp = (strides != nullptr) ? array_min(arr, offset, size, dim, shape, strides) : array_min(arr, offset, size);
	  ret = getNewJObject(env, tmp, "java/lang/Double", "(D)V");
	  break;
	}
	default:break;
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, varr, 0);

  return ret;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    sum
 * Signature: (Ljava/lang/Object;II[I[II)Ljava/lang/Number;
 */
JNIEXPORT jobject JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_sum
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size, jintArray jshape, jintArray jstrides, jint type) {
  int dim;
  jobject ret = nullptr;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }
  void *varr = env->GetPrimitiveArrayCritical((jarray)jarr, nullptr);

  switch (type) {
	case 1: {
	  auto *arr = (int8_t *)(varr);
	  int8_t tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Byte", "(B)V");
	  break;
	}
	case 2: {
	  auto *arr = (int16_t *)(varr);
	  int16_t
		  tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Short", "(S)V");
	  break;
	}
	case 3: {
	  auto *arr = (int32_t *)(varr);
	  int32_t
		  tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Integer", "(I)V");
	  break;
	}
	case 4: {
	  auto *arr = (int64_t *)(varr);
	  int64_t
		  tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Long", "(J)V");
	  break;
	}
	case 5: {
	  auto *arr = (float *)(varr);
	  float_t tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Float", "(F)V");
	  break;
	}
	case 6: {
	  auto *arr = (double *)(varr);
	  double_t tmp = (strides != nullptr) ? array_sum(arr, offset, size, dim, shape, strides) : array_sum(arr, size);
	  ret = getNewJObject(env, tmp, "java/lang/Double", "(D)V");
	  break;
	}
	default:break;
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, varr, 0);

  return ret;
}

/*
 * Class:     org_jetbrains_kotlinx_multik_jni_math_JniMath
 * Method:    cumSum
 * Signature: (Ljava/lang/Object;II[I[ILjava/lang/Object;II)Z
 */
JNIEXPORT jboolean JNICALL Java_org_jetbrains_kotlinx_multik_jni_math_JniMath_cumSum
	(JNIEnv *env, jobject jobj, jobject jarr, jint offset, jint size,
	 jintArray jshape, jintArray jstrides, jobject jout, jint axis, jint type) {
  int dim;
  int *strides = nullptr;
  int *shape;

  if (jstrides != nullptr) {
	dim = env->GetArrayLength(jshape);
	strides = (int *)(env->GetPrimitiveArrayCritical(jstrides, nullptr));
	shape = (int *)(env->GetPrimitiveArrayCritical(jshape, nullptr));
  }
  void *arr = (env->GetPrimitiveArrayCritical((jarray)jarr, nullptr));

  switch (type) {
	case 1: {
	  auto *out = (int8_t *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((int8_t *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((int8_t *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	case 2: {
	  auto *out = (int16_t *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((int16_t *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((int16_t *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	case 3: {
	  auto *out = (int32_t *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((int32_t *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((int32_t *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	case 4: {
	  auto *out = (int64_t *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((int64_t *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((int64_t *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	case 5: {
	  auto *out = (float *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((float *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((float *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	case 6: {
	  auto *out = (double *)(env->GetPrimitiveArrayCritical((jarray)jout, nullptr));
	  (strides != nullptr) ? array_cumsum((double *)arr, out, offset, size, dim, shape, strides)
						   : array_cumsum((double *)arr, out, size);
	  env->ReleasePrimitiveArrayCritical((jarray)jout, out, 0);
	  break;
	}
	default:break;
  }

  if (strides != nullptr) {
	env->ReleasePrimitiveArrayCritical(jstrides, strides, 0);
	env->ReleasePrimitiveArrayCritical(jshape, shape, 0);
  }
  env->ReleasePrimitiveArrayCritical((jarray)jarr, arr, 0);

  return true;
}
