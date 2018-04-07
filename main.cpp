
#include <iostream>

#include <openvr.h>

int main() {

    const auto runtime_installed = vr::VR_IsRuntimeInstalled();
    const auto hmd_present = vr::VR_IsHmdPresent();


    std::cout << "Runtime installed: " << runtime_installed << '\n';
    std::cout << "HMD present: " << hmd_present << '\n';

    if (runtime_installed && hmd_present) {
        std::cout << "Connecting to HMD\n";
        vr::HmdError error;
        auto hmd = vr::VR_Init(&error, vr::EVRApplicationType::VRApplication_Utility);
        if (error == vr::EVRInitError::VRInitError_None) {
            std::cout << "Connected " << hmd << "\n";

            vr::TrackedDevicePose_t pose;
            hmd->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding, 0.0f, &pose, 1);
            std::cout << "Got pose, valid: " << pose.bPoseIsValid << ", connected " << pose.bDeviceIsConnected << '\n';
        } else {
            std::cout << "Failed to connect: error " << vr::VR_GetVRInitErrorAsSymbol(error) << '\n';
        }
        vr::VR_Shutdown();
    }

    return 0;
}
