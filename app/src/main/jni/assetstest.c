/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <assert.h>


// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/MainActivity.java
 */
void
Java_com_mambrosi_testassets_MainActivity_readAssetsNative(JNIEnv *env,
                                                 jobject thiz, jobject assetManager) {

    // use asset manager to open asset by filename
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    assert(NULL != mgr);

    AAsset* testAsset = AAssetManager_open(mgr, "text.csv", AASSET_MODE_UNKNOWN);
    if (testAsset)
    {
        assert(testAsset);

        size_t assetLength = AAsset_getLength(testAsset);

        __android_log_print(ANDROID_LOG_DEBUG, "Native Audio", "Asset file size: %d\n", assetLength);

        char* buffer = (char*) malloc(assetLength + 1);
        AAsset_read(testAsset, buffer, assetLength);
        buffer[assetLength] = 0;

        __android_log_print(ANDROID_LOG_INFO, "Test Asset Manager", "The value is %s", buffer);

        AAsset_close(testAsset);
        free(buffer);
    }
    else
    {
        __android_log_print(ANDROID_LOG_ERROR, "Test Asset Manager", "Cannot open file");
    }
}

