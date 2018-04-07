
#include <iostream>
#include <iomanip>

#include <openvr.h>

namespace {

void print_matrix(const vr::HmdMatrix34_t& matrix) {
    const auto flags(std::cout.flags());
    std::cout << std::fixed << std::setprecision(4);
    const auto column = std::size_t{3};
    std::cout << "X " <<  matrix.m[0][column] << " Y " << matrix.m[1][column] << " Z " << matrix.m[2][column] << '\n';
    std::cout.flags(flags);
}

}

int main() {

    const auto runtime_installed = vr::VR_IsRuntimeInstalled();
    const auto hmd_present = vr::VR_IsHmdPresent();


    std::cout << "Runtime installed: " << runtime_installed << '\n';
    std::cout << "HMD present: " << hmd_present << '\n';

    if (runtime_installed && hmd_present) {
        std::cout << "Connecting to HMD\n";
        vr::HmdError error;
        auto hmd = vr::VR_Init(&error, vr::EVRApplicationType::VRApplication_Overlay);
        if (error == vr::EVRInitError::VRInitError_None) {
            std::cout << "Connected " << hmd << "\n";

            vr::TrackedDevicePose_t pose;
            while (true) {
                hmd->GetDeviceToAbsoluteTrackingPose(vr::TrackingUniverseOrigin::TrackingUniverseStanding, 0.0f, &pose, 1);
                if (pose.bPoseIsValid) {
                    // Notes:
                    // The VR coordinate system is similar to the screen coordinate system.
                    // Looking toward the screen (in the direction of calibration):
                    // +X is to the right
                    // +Y is up
                    // +Z is back (out of the screen)
                    const auto x = pose.mDeviceToAbsoluteTracking.m[0][3];
                    const auto y = pose.mDeviceToAbsoluteTracking.m[1][3];
                    const auto z = pose.mDeviceToAbsoluteTracking.m[2][3];
                    print_matrix(pose.mDeviceToAbsoluteTracking);
                }
            }
        } else {
            std::cout << "Failed to connect: error " << vr::VR_GetVRInitErrorAsSymbol(error) << '\n';
        }
        vr::VR_Shutdown();
    }

    return 0;
}
