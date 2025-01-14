/*
 * Copyright 2020-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license.
 */

import org.gradle.nativeplatform.platform.internal.DefaultNativePlatform

apply(from = "$rootDir/gradle/openblas.gradle")

dependencies {
    api(project(":multik-api"))
}

private val currentOS = DefaultNativePlatform.getCurrentOperatingSystem()
val os = when {
    currentOS.isMacOsX -> "macos"
    currentOS.isLinux -> "linux"
    currentOS.isWindows -> "windows"
    else -> throw Exception("Unsupported platform")
}

tasks.jar {
    from("$buildDir/libs")
    exclude("*.jar")
}

tasks.test {
    dependsOn("multik_jni:build")

    doFirst {
        copy {
            from(fileTree("${project.childProjects["multik_jni"]!!.buildDir}/lib/main/debug").files)
            into("$buildDir/libs")
        }
    }

    systemProperty("java.library.path", "$buildDir/libs")
}
