/* eslint-disable max-classes-per-file */
/* eslint-disable no-restricted-globals */
/* eslint-disable no-undef */
$(document).ready(() => {
  // if deployed to a site supporting SSL, use wss://
  const protocol = document.location.protocol.startsWith('https') ? 'wss://' : 'ws://';
  const webSocket = new WebSocket(protocol + location.host);

  class DeviceData{
    constructor(deviceId){
      this.deviceId= deviceId;
    }
  }

  // All the devices in the list (those that have been sending telemetry)
  class TrackedDevices {
    constructor() {
      this.devices = [];
    }

    // Find a device based on its Id
    findDevice(deviceId) {
      for (let i = 0; i < this.devices.length; ++i) {
        if (this.devices[i].deviceId === deviceId) {
          return this.devices[i];
        }
      }

      return undefined;
    }

    getDevicesCount() {
      return this.devices.length;
    }
  }

  const trackedDevices = new TrackedDevices();

  var prev1_00 = 0;
  var prev2_00 = 0;
  var prev3_00 = 0;
  var prev1_01 = 0;
  var prev2_01 = 0;
  var prev3_01 = 0;
  var prev1_02 = 0;
  var prev2_02 = 0;
  var prev3_02 = 0;
  
  document.getElementById("statueImg").src = "js/penelope.png";

  // Get the context of the canvas element we want to select
  const statueName = document.getElementById('statueId');
  const prof1 = document.getElementById('profile1');
  const prof2 = document.getElementById('profile2');
  const prof3 = document.getElementById('profile3');


  // Manage a list of devices in the UI, and update which device data the chart is showing
  // based on selection
  let needsAutoSelect = true;
  const deviceCount = document.getElementById('deviceCount');
  const listOfDevices = document.getElementById('listOfDevices');
  function OnSelectionChange() {
    const device = trackedDevices.findDevice(listOfDevices[listOfDevices.selectedIndex].text);  
    if (device.deviceId=="dev_00"){
      statueName.textContent = "Penelope";
      thisImg = "js/penelope.png";
      prof1.textContent = prev1_00.toString();
      prof2.textContent = prev2_00.toString();
      prof3.textContent = prev3_00.toString();
    }else if (device.deviceId=="dev_01"){
      statueName.textContent = "Odisseus";
      thisImg = "js/ulisse.png";
      prof1.textContent = prev1_01.toString();
      prof2.textContent = prev2_01.toString();
      prof3.textContent = prev3_01.toString();
    }else if (device.deviceId=="dev_02"){
      statueName.textContent = "Gennaro";
      thisImg = "js/gennaro.png";
      prof1.textContent = prev1_02.toString();
      prof2.textContent = prev2_02.toString();
      prof3.textContent = prev3_02.toString();
    }
    document.getElementById("statueImg").src = thisImg;
  }

  listOfDevices.addEventListener('change',OnSelectionChange);

  // When a web socket message arrives:
  // 1. Unpack it
  // 2. Find or create a cached device to hold the telemetry data
  // 3. Append the telemetry data
  // 4. Update the chart UI
  webSocket.onmessage = function onMessage(message) {
    try {
      const messageData = JSON.parse(message.data);
      console.log(messageData);

      // find or add device to list of tracked devices
      const existingDeviceData = trackedDevices.findDevice(messageData.DeviceId);
      

      if (existingDeviceData) {
        if (messageData.IotData.dev_id == "dev_00"){
          if (messageData.IotData.profile_id=="Hugo"){
            ++prev1_00;
            prof1.textContent = prev1_00.toString(); 
          }else if(messageData.IotData.profile_id == "Maria"){
            ++prev2_00;
            prof2.textContent = prev2_00.toString(); 
          }else if(messageData.IotData.profile_id == "Ettore"){
            ++prev3_00;
            prof3.textContent = prev3_00.toString(); 
          }
        }else if (messageData.IotData.dev_id == "dev_01"){
            if (messageData.IotData.profile_id=="Hugo"){
              ++prev1_01;
              prof1.textContent = prev1_01.toString(); 
            }else if(messageData.IotData.profile_id == "Maria"){
              ++prev2_01;
              prof2.textContent = prev2_01.toString(); 
            }else if(messageData.IotData.profile_id == "Ettore"){
              ++prev3_01;
              prof3.textContent = prev3_01.toString(); 
            }
        }else if (messageData.IotData.dev_id == "dev_02"){
          if (messageData.IotData.profile_id=="Hugo"){
            prev1_02++;
          }else if(messageData.IotData.profile_id == "Maria"){
            prev2_02++;
          }else if(messageData.IotData.profile_id == "Ettore"){
            prev3_02++;
          }
        }
      } else {
        //new device
        const newDeviceData = new DeviceData(messageData.DeviceId);
        trackedDevices.devices.push(newDeviceData);
        const numDevices = trackedDevices.getDevicesCount();
        deviceCount.innerText = numDevices === 1 ? `${numDevices} device` : `${numDevices} devices`;
        if (messageData.IotData.dev_id == "dev_00"){
          statueName.textContent = "Penelope";

          if (messageData.IotData.profile_id=="Hugo"){
            ++prev1_00;
            prof1.textContent = prev1_00.toString(); 
          }else if(messageData.IotData.profile_id == "Maria"){
            ++prev2_00;
            prof2.textContent = prev2_00.toString(); 
          }else if(messageData.IotData.profile_id == "Ettore"){
            ++prev3_00;
            prof3.textContent = prev3_00.toString(); 
          }
        }else if (messageData.IotData.dev_id == "dev_01"){

            if (messageData.IotData.profile_id=="Hugo"){
              prev1_01++;
            }else if(messageData.IotData.profile_id == "Maria"){
              prev2_01++;
            }else if(messageData.IotData.profile_id == "Ettore"){
              prev3_01++;
            }
        }else if (messageData.IotData.dev_id == "dev_02"){
          if (messageData.IotData.profile_id=="Hugo"){
            prev1_02++;
          }else if(messageData.IotData.profile_id == "Maria"){
            prev2_02++;
          }else if(messageData.IotData.profile_id == "Ettore"){
            prev3_02++;
          }
        }
        // add device to the UI list
        const node = document.createElement('option');
        const nodeText = document.createTextNode(messageData.DeviceId);
        node.appendChild(nodeText);
        listOfDevices.appendChild(node);

        // if this is the first device being discovered, auto-select it
        if (needsAutoSelect) {
          needsAutoSelect = false;
          listOfDevices.selectedIndex = 0;
          OnSelectionChange();
        }
      }

    } catch (err) {
      console.error(err);
    }
  };
});