/*
 * Copyright 2017 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * This file was autogenerated from GrDitherEffect.fp; do not modify.
 */
#include "GrDitherEffect.h"
#if SK_SUPPORT_GPU
#include "glsl/GrGLSLColorSpaceXformHelper.h"
#include "glsl/GrGLSLFragmentProcessor.h"
#include "glsl/GrGLSLFragmentShaderBuilder.h"
#include "glsl/GrGLSLProgramBuilder.h"
#include "SkSLCPP.h"
#include "SkSLUtil.h"
class GrGLSLDitherEffect : public GrGLSLFragmentProcessor {
public:
    GrGLSLDitherEffect() {}
    void emitCode(EmitArgs& args) override {
        GrGLSLFPFragmentBuilder* fragBuilder = args.fFragBuilder;
        const GrDitherEffect& _outer = args.fFp.cast<GrDitherEffect>();
        (void)_outer;
        fragBuilder->codeAppendf(
                "float value;\nfloat range;\n@switch (%d) {\n    case 0:\n        range = "
                "0.0039215686274509803;\n        break;\n    case 1:\n        range = "
                "0.015873015873015872;\n        break;\n    default:\n        range = "
                "0.0083333333333333332;\n        break;\n}\n@if (sk_Caps.integerSupport) {\n    "
                "int x = int(sk_FragCoord.x);\n    int y = int(sk_FragCoord.y);\n    uint m = "
                "uint((((((y & 1) << 5 | (x & 1) << 4) | (y & 2) << 2) | (x & 2) << 1) | (y & 4) "
                ">> 1) | (x & 4) >> 2);\n    value = float(m) / 64.0 - 0.4921875;\n} else {\n    "
                "value = fract(sin(dot(sk_FragCoord.xy, vec2(12.989800000000001, "
                "78.233000000000004))) * 43758.545299999998) - 0.5;\n}\n%s = vec4(clamp(%s.xyz + "
                "value * range, 0.0, %s.w), %s.w);\n",
                _outer.rangeType(), args.fOutputColor,
                args.fInputColor ? args.fInputColor : "vec4(1)",
                args.fInputColor ? args.fInputColor : "vec4(1)",
                args.fInputColor ? args.fInputColor : "vec4(1)");
    }

private:
    void onSetData(const GrGLSLProgramDataManager& pdman,
                   const GrFragmentProcessor& _proc) override {}
};
GrGLSLFragmentProcessor* GrDitherEffect::onCreateGLSLInstance() const {
    return new GrGLSLDitherEffect();
}
void GrDitherEffect::onGetGLSLProcessorKey(const GrShaderCaps& caps,
                                           GrProcessorKeyBuilder* b) const {
    b->add32(fRangeType);
}
bool GrDitherEffect::onIsEqual(const GrFragmentProcessor& other) const {
    const GrDitherEffect& that = other.cast<GrDitherEffect>();
    (void)that;
    if (fRangeType != that.fRangeType) return false;
    return true;
}
GR_DEFINE_FRAGMENT_PROCESSOR_TEST(GrDitherEffect);
#if GR_TEST_UTILS
sk_sp<GrFragmentProcessor> GrDitherEffect::TestCreate(GrProcessorTestData* testData) {
    float range = testData->fRandom->nextRangeF(0.001f, 0.05f);
    return sk_sp<GrFragmentProcessor>(new GrDitherEffect(range));
}
#endif
#endif
