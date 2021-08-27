package org.jetbrains.kotlinx.multik.jvm.linalg

import org.jetbrains.kotlinx.multik.api.d2arrayComplex
import org.jetbrains.kotlinx.multik.api.mk
import org.jetbrains.kotlinx.multik.ndarray.complex.ComplexDouble
import org.jetbrains.kotlinx.multik.ndarray.data.*
import org.jetbrains.kotlinx.multik.ndarray.operations.mapMultiIndexed
import kotlin.math.abs
import kotlin.math.sqrt


internal fun gramShmidtComplexDouble(a: MultiArray<ComplexDouble, D2>): D2Array<ComplexDouble> {
    val precision = 1e-16

    // ans = a.T
    // we need fair transpose: elements in ans matrix row should be consequently in memory
    val ans: D2Array<ComplexDouble> = mk.d2arrayComplex(a.shape[1], a.shape[0]) { ComplexDouble.zero } //(a.deepCopy() as D2Array<ComplexDouble>)
    for (i in 0 until ans.shape[0]) {
        for (j in 0 until ans.shape[1]) {
            ans[i, j] = a[j, i]
        }
    }


    //normalize all vectors to have unit length
    for (i in 0 until ans.shape[0]) {
        var norm = 0.0
        for (j in 0 until ans.shape[1]) {
            norm += (ans[i, j] * ans[i, j].conjugate()).re
        }
        norm = sqrt(abs(norm))
        if (norm < precision) {
            continue;
        }
        for (j in 0 until ans.shape[1]) {
            ans[i, j] = ans[i, j] / norm
        }
    }

    for (currow in 1 until ans.shape[0]) {
        // make curcol vector orthogonal to previous vectors
        for (i in 0 until currow) {
            var scalProd = ComplexDouble.zero
            for (j in 0 until ans.shape[1]) {
                scalProd += ans[i, j] * ans[currow, j].conjugate()
            }
            for (j in 0 until ans.shape[1]) {
                ans[currow, j] = ans[currow, j] - scalProd.conjugate() * ans[i, j]
            }
        }
        // curcol vector normalization
        var norm = 0.0
        for (j in 0 until ans.shape[1]) {
            norm += (ans[currow, j] * ans[currow, j].conjugate()).re
        }
        norm = sqrt(abs(norm))
        if(norm < precision) {
            continue
        }
        for (j in 0 until ans.shape[1]) {
            ans[currow, j] = ans[currow, j] / norm
        }
    }

    return ans.transpose()
}