/*
 * Copyright 2020-2021 JetBrains s.r.o. Use of this source code is governed by the Apache 2.0 license.
 */

import org.jetbrains.kotlin.gradle.tasks.KotlinCompile

buildscript {
    repositories {
        mavenCentral()
    }
}

plugins {
    val kotlin_version: String by System.getProperties()
    val nexus_version: String by System.getProperties()

    kotlin("jvm") version kotlin_version
    id("io.codearte.nexus-staging") version nexus_version
}

val kotlin_version: String by System.getProperties()
val multik_version: String by project
val unpublished = listOf("multik", "multik_jni")

allprojects {
    repositories {
        mavenCentral()
    }

    group = "org.jetbrains.kotlinx"
    version = multik_version

    tasks.withType<KotlinCompile> {
        kotlinOptions.jvmTarget = "1.8"
    }
}

subprojects {
    if (!this.name.contains("jni")) {
        apply(plugin = "kotlin")

        dependencies {
            testImplementation(kotlin("test"))
            testImplementation(kotlin("test-junit"))
        }
    }
}

configure(subprojects.filter { it.name !in unpublished }) {
    apply("$rootDir/gradle/publish.gradle")
}