#define LOG_TAG "vendor.samsung.hardware.gnss@1.0-service"

#include <android/hardware/gnss/1.0/IGnss.h>
#include <android/hardware/gnss/1.1/IGnss.h>
#include <android/hardware/gnss/2.0/IGnss.h>
#include <android/hardware/gnss/2.1/IGnss.h>
#include <vendor/samsung/hardware/gnss/1.0/ISlsiGnss.h>
#include <hidl/LegacySupport.h>
#include <binder/ProcessState.h>

using IGnss_V1_0 = android::hardware::gnss::V1_0::IGnss;
using IGnss_V1_1 = android::hardware::gnss::V1_1::IGnss;
using IGnss_V2_0 = android::hardware::gnss::V2_0::IGnss;
using IGnss_V2_1 = android::hardware::gnss::V2_1::IGnss;
using ISlsiGnss_V1_0 = vendor::samsung::hardware::gnss::V1_0::ISlsiGnss;

using android::hardware::configureRpcThreadpool;
using android::hardware::registerPassthroughServiceImplementation;
using android::hardware::joinRpcThreadpool;

using android::status_t;
using android::OK;

int main(void)
{
   ALOGI("%s", __FUNCTION__);

   /* We are going to start two services here */
   configureRpcThreadpool(3, true);
   status_t status_IGnss_v1_0;
   status_t status_IGnss_v1_1;
   status_t status_IGnss_v2_0;
   status_t status_IGnss_v2_1;
   status_t status_ISlsiGnss_v1_0;
   
   status_IGnss_v2_1 = registerPassthroughServiceImplementation<IGnss_V2_1>();
   if(status_IGnss_v2_1 != OK)
   {   
      ALOGE("Error while registering IGnss_V2_1 %d", status_IGnss_v2_1);
      status_IGnss_v2_0 = registerPassthroughServiceImplementation<IGnss_V2_0>();
      if(status_IGnss_v2_0 != OK)
      {
          ALOGE("Error while registering IGnss_V2_0: %d", status_IGnss_v2_0);
          status_IGnss_v1_1 = registerPassthroughServiceImplementation<IGnss_V1_1>();
          if(status_IGnss_v1_1 != OK)
          {
              ALOGE("Error while registering IGnss_V1_1: %d", status_IGnss_v1_1);
              status_IGnss_v1_0 = registerPassthroughServiceImplementation<IGnss_V1_0>();
              if(status_IGnss_v1_0 != OK)
              {
                  ALOGE("Error while registering IGnss_V1_0: %d", status_IGnss_v1_0);
                  return(-1);
              }else{
                  ALOGE("Success to registering IGnss_V1_0:%d", status_IGnss_v1_0);
              }
          }else{
              ALOGE("Success to registering IGNSS_v1_1 : %d", status_IGnss_v1_1);
          }
      }else{
          ALOGE("Success to registering IGNSS_v2_0 : %d", status_IGnss_v2_0);
      }
   }else{
       ALOGE("Success to registering IGNSS_v2_1 : %d", status_IGnss_v2_1);
   }

   status_ISlsiGnss_v1_0 = registerPassthroughServiceImplementation<ISlsiGnss_V1_0>();
   if(status_ISlsiGnss_v1_0 != OK)
   {
       ALOGE("Error while registering ISlsiGnss_V1_0: %d", status_ISlsiGnss_v1_0);
       return(-1);
   } else{
       ALOGE("Success to registering ISlsiGnss_V1_0:%d", status_ISlsiGnss_v1_0);
   }

   joinRpcThreadpool();

   return(0);
}

