#pragma once

#include <memory>

#include "../../library/SceneObjectLibrary.h"

#include "WorkspaceNodeCamera.h"
#include "WorkspaceNodeExternalObject.h"
#include "WorkspaceNodeSceneObject.h"
#include "WorkspaceNodeTime.h"
#include "WorkspaceNodeText.h"

#include "comparison/WorkspaceNodeCmpEqual.h"
#include "comparison/WorkspaceNodeCmpNotEqual.h"
#include "comparison/WorkspaceNodeCmpSmaller.h"
#include "comparison/WorkspaceNodeCmpSmallerEqual.h"

#include "conversion/float/WorkspaceNodeConvFloatToMat4.h"
#include "conversion/float/WorkspaceNodeConvFloatToQuat.h"
#include "conversion/float/WorkspaceNodeConvFloatToVec3.h"
#include "conversion/float/WorkspaceNodeConvFloatToVec4.h"
#include "conversion/mat4/WorkspaceNodeConvMat4ToFloat.h"
#include "conversion/mat4/WorkspaceNodeConvMat4ToQuat.h"
#include "conversion/mat4/WorkspaceNodeConvMat4ToVec4.h"
#include "conversion/quat/WorkspaceNodeConvAngleAxisToQuat.h"
#include "conversion/quat/WorkspaceNodeConvEulerToQuat.h"
#include "conversion/quat/WorkspaceNodeConvVec3Vec3ToQuat.h"
#include "conversion/quat/WorkspaceNodeConvQuatToAngleAxis.h"
#include "conversion/quat/WorkspaceNodeConvQuatToEuler.h"
#include "conversion/quat/WorkspaceNodeConvQuatToFloat.h"
#include "conversion/quat/WorkspaceNodeConvQuatToMat4.h"
#include "conversion/vec3/WorkspaceNodeConvVec3FloatToVec4.h"
#include "conversion/vec3/WorkspaceNodeConvVec3ToFloat.h"
#include "conversion/vec4/WorkspaceNodeConvVec4ToFloat.h"
#include "conversion/vec4/WorkspaceNodeConvVec4ToMat4.h"
#include "conversion/vec4/WorkspaceNodeConvVec4ToVec3Float.h"

#include "logical/WorkspaceNodeBoolAnd.h"
#include "logical/WorkspaceNodeBoolNot.h"
#include "logical/WorkspaceNodeBoolOr.h"
#include "logical/WorkspaceNodeBoolValue.h"
#include "logical/WorkspaceNodeBoolXor.h"
#include "logical/WorkspaceNodePick.h"

#include "function/float/WorkspaceNodeAcos.h"
#include "function/float/WorkspaceNodeAbs.h"
#include "function/float/WorkspaceNodeAsin.h"
#include "function/float/WorkspaceNodeCeil.h"
#include "function/float/WorkspaceNodeClamp.h"
#include "function/float/WorkspaceNodeCos.h"
#include "function/float/WorkspaceNodeFloatMix.h"
#include "function/float/WorkspaceNodeFloor.h"
#include "function/float/WorkspaceNodeMod.h"
#include "function/float/WorkspaceNodeSign.h"
#include "function/float/WorkspaceNodeSin.h"
#include "function/quat/WorkspaceNodeQuatConjugate.h"
#include "function/quat/WorkspaceNodeQuatInverse.h"
#include "function/quat/WorkspaceNodeQuatLength.h"
#include "function/quat/WorkspaceNodeQuatLerp.h"
#include "function/quat/WorkspaceNodeQuatNormalize.h"
#include "function/quat/WorkspaceNodeQuatSlerp.h"
#include "function/quat/WorkspaceNodeQuatVec3Quat.h"
#include "function/mat4/WorkspaceNodeMat4Decompose.h"
#include "function/mat4/WorkspaceNodeMat4Determinant.h"
#include "function/mat4/WorkspaceNodeMat4Inverse.h"
#include "function/mat4/WorkspaceNodeMat4Transpose.h"
#include "function/vec3/WorkspaceNodeVec3Normalize.h"
#include "function/vec3/WorkspaceNodeVec3Length.h"
#include "function/vec3/WorkspaceNodeVec3Mix.h"
#include "function/vec4/WorkspaceNodeVec4Normalize.h"
#include "function/vec4/WorkspaceNodeVec4Mix.h"

#include "operator/WorkspaceNodeFloatAdd.h"
#include "operator/WorkspaceNodeFloatDivide.h"
#include "operator/WorkspaceNodeFloatMultiply.h"
#include "operator/WorkspaceNodeFloatMultMat4.h"
#include "operator/WorkspaceNodeFloatMultQuat.h"
#include "operator/WorkspaceNodeFloatMultVec3.h"
#include "operator/WorkspaceNodeFloatMultVec4.h"
#include "operator/WorkspaceNodeFloatPower.h"
#include "operator/WorkspaceNodeFloatSubstract.h"
#include "operator/WorkspaceNodeMat4Add.h"
#include "operator/WorkspaceNodeMat4Mult.h"
#include "operator/WorkspaceNodeMat4MultVec4.h"
#include "operator/WorkspaceNodeMat4Substract.h"
#include "operator/WorkspaceNodeQuatMult.h"
#include "operator/WorkspaceNodeVec3Add.h"
#include "operator/WorkspaceNodeVec3Dot.h"
#include "operator/WorkspaceNodeVec3Multiply.h"
#include "operator/WorkspaceNodeVec3Substract.h"
#include "operator/WorkspaceNodeVec4Add.h"
#include "operator/WorkspaceNodeVec4Dot.h"
#include "operator/WorkspaceNodeVec4Multiply.h"
#include "operator/WorkspaceNodeVec4Substract.h"

#include "projection/WorkspaceNodeProjOrtho.h"
#include "projection/WorkspaceNodeProjPerspective.h"
#include "projection/WorkspaceNodeProjFrustum.h"

#include "value/WorkspaceNodeFloatValue.h"
#include "value/WorkspaceNodeVec3Value.h"
#include "value/WorkspaceNodeVec4Value.h"
#include "value/WorkspaceNodeMat4Value.h"
#include "value/WorkspaceNodeQuatValue.h"
#include "value/transformation/WorkspaceNodeTransfTranslValue.h"
#include "value/transformation/WorkspaceNodeTransfScaleValue.h"
#include "value/transformation/WorkspaceNodeTransfRotationValue.h"

#include "transformation/WorkspaceNodeTransfLookAt.h"
#include "transformation/WorkspaceNodeTransfRotationVector.h"
#include "transformation/WorkspaceNodeTransfRotationX.h"
#include "transformation/WorkspaceNodeTransfRotationY.h"
#include "transformation/WorkspaceNodeTransfRotationZ.h"
#include "transformation/WorkspaceNodeTransfScale.h"
#include "transformation/WorkspaceNodeTransfTransl.h"

namespace AVC3T {
    class WorkspaceNodeBinder {
      public:
        //----------------------------------------------------------
        // VALUES
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeFloatValue> NewFloatValue() {
            return std::make_shared<WorkspaceNodeFloatValue>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Value> NewVec3Value() {
            return std::make_shared<WorkspaceNodeVec3Value>();
        }

        static std::shared_ptr<WorkspaceNodeVec4Value> NewVec4Value() {
            return std::make_shared<WorkspaceNodeVec4Value>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Value> NewMat4Value() {
            return std::make_shared<WorkspaceNodeMat4Value>();
        }

        static std::shared_ptr<WorkspaceNodeQuatValue> NewQuatValue() {
            return std::make_shared<WorkspaceNodeQuatValue>();
        }

        static std::shared_ptr<WorkspaceNodeTransfTranslValue> NewTransfTranslValue() {
            return std::make_shared<WorkspaceNodeTransfTranslValue>();
        }

        static std::shared_ptr<WorkspaceNodeTransfScaleValue> NewTransfScaleValue() {
            return std::make_shared<WorkspaceNodeTransfScaleValue>();
        }

        static std::shared_ptr<WorkspaceNodeTransfRotationValue> NewTransfRotationValue() {
            return std::make_shared<WorkspaceNodeTransfRotationValue>();
        }

        //----------------------------------------------------------
        // OPERATORS
        //----------------------------------------------------------
        //---------------------
        // Float
        //---------------------
        static std::shared_ptr<WorkspaceNodeFloatAdd> NewFloatAdd() {
            return std::make_shared<WorkspaceNodeFloatAdd>();
        }

        static std::shared_ptr<WorkspaceNodeFloatSubstract> NewFloatSubstract() {
            return std::make_shared<WorkspaceNodeFloatSubstract>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMultiply> NewFloatMultiply() {
            return std::make_shared<WorkspaceNodeFloatMultiply>();
        }

        static std::shared_ptr<WorkspaceNodeFloatDivide> NewFloatDivide() {
            return std::make_shared<WorkspaceNodeFloatDivide>();
        }

        static std::shared_ptr<WorkspaceNodeFloatPower> NewFloatPower() {
            return std::make_shared<WorkspaceNodeFloatPower>();
        }

        //---------------------
        // Vec3
        //---------------------
        static std::shared_ptr<WorkspaceNodeVec3Add> NewVec3Add() {
            return std::make_shared<WorkspaceNodeVec3Add>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Substract> NewVec3Substract() {
            return std::make_shared<WorkspaceNodeVec3Substract>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Multiply> NewVec3Multiply() {
            return std::make_shared<WorkspaceNodeVec3Multiply>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Dot> NewVec3Dot() {
            return std::make_shared<WorkspaceNodeVec3Dot>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMultVec3> NewFloatMultVec3() {
            return std::make_shared<WorkspaceNodeFloatMultVec3>();
        }

        //---------------------
        // Vec4
        //---------------------
        static std::shared_ptr<WorkspaceNodeVec4Add> NewVec4Add() {
            return std::make_shared<WorkspaceNodeVec4Add>();
        }

        static std::shared_ptr<WorkspaceNodeVec4Substract> NewVec4Substract() {
            return std::make_shared<WorkspaceNodeVec4Substract>();
        }

        static std::shared_ptr<WorkspaceNodeVec4Multiply> NewVec4Multiply() {
            return std::make_shared<WorkspaceNodeVec4Multiply>();
        }

        static std::shared_ptr<WorkspaceNodeVec4Dot> NewVec4Dot() {
            return std::make_shared<WorkspaceNodeVec4Dot>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMultVec4> NewFloatMultVec4() {
            return std::make_shared<WorkspaceNodeFloatMultVec4>();
        }

        static std::shared_ptr<WorkspaceNodeMat4MultVec4> NewMat4MultVec4() {
            return std::make_shared<WorkspaceNodeMat4MultVec4>();
        }

        //---------------------
        // Mat4
        //---------------------
        static std::shared_ptr<WorkspaceNodeMat4Add> NewMat4Add() {
            return std::make_shared<WorkspaceNodeMat4Add>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Substract> NewMat4Substract() {
            return std::make_shared<WorkspaceNodeMat4Substract>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Mult> NewMat4Mult() {
            return std::make_shared<WorkspaceNodeMat4Mult>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMultMat4> NewFloatMultMat4() {
            return std::make_shared<WorkspaceNodeFloatMultMat4>();
        }

        //---------------------
        // Quat
        //---------------------
        static std::shared_ptr<WorkspaceNodeQuatMult> NewQuatMult() {
            return std::make_shared<WorkspaceNodeQuatMult>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMultQuat> NewFloatMultQuat() {
            return std::make_shared<WorkspaceNodeFloatMultQuat>();
        }

        //----------------------------------------------------------
        // TRANSFORMATIONS
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeTransfTransl> NewTransfTransl() {
            return std::make_shared<WorkspaceNodeTransfTransl>();
        }

        static std::shared_ptr<WorkspaceNodeTransfScale> NewTransfScale() {
            return std::make_shared<WorkspaceNodeTransfScale>();
        }

        static std::shared_ptr<WorkspaceNodeTransfRotationX> NewTransfRotationX() {
            return std::make_shared<WorkspaceNodeTransfRotationX>();
        }

        static std::shared_ptr<WorkspaceNodeTransfRotationY> NewTransfRotationY() {
            return std::make_shared<WorkspaceNodeTransfRotationY>();
        }

        static std::shared_ptr<WorkspaceNodeTransfRotationZ> NewTransfRotationZ() {
            return std::make_shared<WorkspaceNodeTransfRotationZ>();
        }

        static std::shared_ptr<WorkspaceNodeTransfRotationVector> NewTransfRotationVector() {
            return std::make_shared<WorkspaceNodeTransfRotationVector>();
        }
        static std::shared_ptr<WorkspaceNodeTransfLookAt> NewTransfLookAt() {
            return std::make_shared<WorkspaceNodeTransfLookAt>();
        }

        //----------------------------------------------------------
        // FUNCTIONS
        //----------------------------------------------------------
        //---------------------
        // Float
        //---------------------
        static std::shared_ptr<WorkspaceNodeSin> NewSin() {
            return std::make_shared<WorkspaceNodeSin>();
        }

        static std::shared_ptr<WorkspaceNodeCos> NewCos() {
            return std::make_shared<WorkspaceNodeCos>();
        }

        static std::shared_ptr<WorkspaceNodeAsin> NewAsin() {
            return std::make_shared<WorkspaceNodeAsin>();
        }

        static std::shared_ptr<WorkspaceNodeAcos> NewAcos() {
            return std::make_shared<WorkspaceNodeAcos>();
        }

        static std::shared_ptr<WorkspaceNodeAbs> NewAbs() {
            return std::make_shared<WorkspaceNodeAbs>();
        }

        static std::shared_ptr<WorkspaceNodeCeil> NewCeil() {
            return std::make_shared<WorkspaceNodeCeil>();
        }

        static std::shared_ptr<WorkspaceNodeFloor> NewFloor() {
            return std::make_shared<WorkspaceNodeFloor>();
        }

        static std::shared_ptr<WorkspaceNodeClamp> NewClamp() {
            return std::make_shared<WorkspaceNodeClamp>();
        }

        static std::shared_ptr<WorkspaceNodeMod> NewMod() {
            return std::make_shared<WorkspaceNodeMod>();
        }

        static std::shared_ptr<WorkspaceNodeSign> NewSign() {
            return std::make_shared<WorkspaceNodeSign>();
        }

        static std::shared_ptr<WorkspaceNodeFloatMix> NewFloatMix() {
            return std::make_shared<WorkspaceNodeFloatMix>();
        }

        //---------------------
        // Vec3
        //---------------------
        static std::shared_ptr<WorkspaceNodeVec3Normalize> NewVec3Normalize() {
            return std::make_shared<WorkspaceNodeVec3Normalize>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Length> NewVec3Length() {
            return std::make_shared<WorkspaceNodeVec3Length>();
        }

        static std::shared_ptr<WorkspaceNodeVec3Mix> NewVec3Mix() {
            return std::make_shared<WorkspaceNodeVec3Mix>();
        }

        //---------------------
        // Vec4
        //---------------------
        static std::shared_ptr<WorkspaceNodeVec4Normalize> NewVec4Normalize() {
            return std::make_shared<WorkspaceNodeVec4Normalize>();
        }

        static std::shared_ptr<WorkspaceNodeVec4Mix> NewVec4Mix() {
            return std::make_shared<WorkspaceNodeVec4Mix>();
        }

        //---------------------
        // Mat4
        //---------------------
        static std::shared_ptr<WorkspaceNodeMat4Decompose> NewMat4Decompose() {
            return std::make_shared<WorkspaceNodeMat4Decompose>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Determinant> NewMat4Determinant() {
            return std::make_shared<WorkspaceNodeMat4Determinant>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Inverse> NewMat4Inverse() {
            return std::make_shared<WorkspaceNodeMat4Inverse>();
        }

        static std::shared_ptr<WorkspaceNodeMat4Transpose> NewMat4Tranpose() {
            return std::make_shared<WorkspaceNodeMat4Transpose>();
        }

        //---------------------
        // Quat
        //---------------------
        static std::shared_ptr<WorkspaceNodeQuatConjugate> NewQuatConjugate() {
            return std::make_shared<WorkspaceNodeQuatConjugate>();
        }

        static std::shared_ptr<WorkspaceNodeQuatInverse> NewQuatInverse() {
            return std::make_shared<WorkspaceNodeQuatInverse>();
        }

        static std::shared_ptr<WorkspaceNodeQuatNormalize> NewQuatNormalize() {
            return std::make_shared<WorkspaceNodeQuatNormalize>();
        }

        static std::shared_ptr<WorkspaceNodeQuatLength> NewQuatLength() {
            return std::make_shared<WorkspaceNodeQuatLength>();
        }

        static std::shared_ptr<WorkspaceNodeQuatLerp> NewQuatLerp() {
            return std::make_shared<WorkspaceNodeQuatLerp>();
        }

        static std::shared_ptr<WorkspaceNodeQuatSlerp> NewQuatSlerp() {
            return std::make_shared<WorkspaceNodeQuatSlerp>();
        }

        static std::shared_ptr<WorkspaceNodeQuatVec3Quat> NewQuatVec3Quat() {
            return std::make_shared<WorkspaceNodeQuatVec3Quat>();
        }

        //----------------------------------------------------------
        // CONVERSION
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeConvFloatToVec3> NewConvFloatToVec3() {
            return std::make_shared<WorkspaceNodeConvFloatToVec3>();
        }

        static std::shared_ptr<WorkspaceNodeConvFloatToVec4> NewConvFloatToVec4() {
            return std::make_shared<WorkspaceNodeConvFloatToVec4>();
        }

        static std::shared_ptr<WorkspaceNodeConvFloatToMat4> NewConvFloatToMat4() {
            return std::make_shared<WorkspaceNodeConvFloatToMat4>();
        }

        static std::shared_ptr<WorkspaceNodeConvFloatToQuat> NewConvFloatToQuat() {
            return std::make_shared<WorkspaceNodeConvFloatToQuat>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec3ToFloat> NewConvVec3ToFloat() {
            return std::make_shared<WorkspaceNodeConvVec3ToFloat>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec3FloatToVec4> NewConvVec3FloatToVec3() {
            return std::make_shared<WorkspaceNodeConvVec3FloatToVec4>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec4ToFloat> NewConvVec4ToFloat() {
            return std::make_shared<WorkspaceNodeConvVec4ToFloat>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec4ToVec3Float> NewConvVec4ToVec3Float() {
            return std::make_shared<WorkspaceNodeConvVec4ToVec3Float>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec4ToMat4> NewConvVec4ToMat4() {
            return std::make_shared<WorkspaceNodeConvVec4ToMat4>();
        }

        static std::shared_ptr<WorkspaceNodeConvMat4ToFloat> NewConvMat4ToFloat() {
            return std::make_shared<WorkspaceNodeConvMat4ToFloat>();
        }

        static std::shared_ptr<WorkspaceNodeConvMat4ToVec4> NewConvMat4ToVec4() {
            return std::make_shared<WorkspaceNodeConvMat4ToVec4>();
        }

        static std::shared_ptr<WorkspaceNodeConvMat4ToQuat> NewConvMat4ToQuat() {
            return std::make_shared<WorkspaceNodeConvMat4ToQuat>();
        }

        static std::shared_ptr<WorkspaceNodeConvQuatToFloat> NewConvQuatToFloat() {
            return std::make_shared<WorkspaceNodeConvQuatToFloat>();
        }

        static std::shared_ptr<WorkspaceNodeConvQuatToMat4> NewConvQuatToMat4() {
            return std::make_shared<WorkspaceNodeConvQuatToMat4>();
        }

        static std::shared_ptr<WorkspaceNodeConvQuatToAngleAxis> NewConvQuatToAngleAxis() {
            return std::make_shared<WorkspaceNodeConvQuatToAngleAxis>();
        }

        static std::shared_ptr<WorkspaceNodeConvQuatToEuler> NewConvQuatToEuler() {
            return std::make_shared<WorkspaceNodeConvQuatToEuler>();
        }

        static std::shared_ptr<WorkspaceNodeConvAngleAxisToQuat> NewConvAngleAxisToQuat() {
            return std::make_shared<WorkspaceNodeConvAngleAxisToQuat>();
        }

        static std::shared_ptr<WorkspaceNodeConvEulerToQuat> NewConvEulerToQuat() {
            return std::make_shared<WorkspaceNodeConvEulerToQuat>();
        }

        static std::shared_ptr<WorkspaceNodeConvVec3Vec3ToQuat> NewConvVec3Vec3ToQuat() {
            return std::make_shared<WorkspaceNodeConvVec3Vec3ToQuat>();
        }

        //----------------------------------------------------------
        // PROJECTION
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeProjOrtho> NewProjOrtho() {
            return std::make_shared<WorkspaceNodeProjOrtho>();
        }

        static std::shared_ptr<WorkspaceNodeProjPerspective> NewProjPerspective() {
            return std::make_shared<WorkspaceNodeProjPerspective>();
        }

        static std::shared_ptr<WorkspaceNodeProjFrustum> NewProjFrustum() {
            return std::make_shared<WorkspaceNodeProjFrustum>();
        }

        //----------------------------------------------------------
        // LOGICAL
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeBoolValue> NewBoolValue() {
            return std::make_shared<WorkspaceNodeBoolValue>();
        }

        static std::shared_ptr<WorkspaceNodeBoolAnd> NewBoolAnd() {
            return std::make_shared<WorkspaceNodeBoolAnd>();
        }

        static std::shared_ptr<WorkspaceNodeBoolOr> NewBoolOr() {
            return std::make_shared<WorkspaceNodeBoolOr>();
        }

        static std::shared_ptr<WorkspaceNodeBoolXor> NewBoolXor() {
            return std::make_shared<WorkspaceNodeBoolXor>();
        }

        static std::shared_ptr<WorkspaceNodeBoolNot> NewBoolNot() {
            return std::make_shared<WorkspaceNodeBoolNot>();
        }

        static std::shared_ptr<WorkspaceNodePick> NewPick() {
            return std::make_shared<WorkspaceNodePick>();
        }

        //---------------------
        // Quat
        //---------------------
        static std::shared_ptr<WorkspaceNodeCmpEqual> NewCmpEqual() {
            return std::make_shared<WorkspaceNodeCmpEqual>();
        }

        static std::shared_ptr<WorkspaceNodeCmpNotEqual> NewCmpNotEqual() {
            return std::make_shared<WorkspaceNodeCmpNotEqual>();
        }

        static std::shared_ptr<WorkspaceNodeCmpSmaller> NewCmpSmaller() {
            return std::make_shared<WorkspaceNodeCmpSmaller>();
        }

        static std::shared_ptr<WorkspaceNodeCmpSmallerEqual> NewCmpSmallerEqual() {
            return std::make_shared<WorkspaceNodeCmpSmallerEqual>();
        }

        //----------------------------------------------------------
        // OBJECTS
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeSceneObject> NewSceneObject(Scene& scene, const std::string& name) {
            return std::make_shared<WorkspaceNodeSceneObject>(scene, name);
        }

        static std::shared_ptr<WorkspaceNodeExternalObject> NewExternalObject(Scene& scene) {
            return std::make_shared<WorkspaceNodeExternalObject>(scene);
        }

        //----------------------------------------------------------
        // MISC
        //----------------------------------------------------------
        static std::shared_ptr<WorkspaceNodeCamera> NewCamera(Scene& scene) {
            return std::make_shared<WorkspaceNodeCamera>(scene);
        }

        static std::shared_ptr<WorkspaceNodeTime> NewTime() {
            return std::make_shared<WorkspaceNodeTime>();
        }

        static std::shared_ptr<WorkspaceNodeText> NewTextArea() {
            return std::make_shared<WorkspaceNodeText>(true);
        }
    };
}