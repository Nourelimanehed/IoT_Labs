// The code here implements the transport protocol between the controls and the Iot application.
// It can be changed to use alternate transport mechanisms and formatting as required for a particular platform.
var statusRequests = 0;
var statusFails = 0;
var statusAborted = false;
var statusHttpRequest = null;
var messageQueue = [];
var messageHttpRequest = null;
var firstResponse = true;

document.title = "Virtual Front Panel (Raspberry Pi)"

function statusRequest() {
   statusHttpRequest = new XMLHttpRequest();
   statusHttpRequest.timeout = 30000;
   statusHttpRequest.onreadystatechange = function() {
      if (statusHttpRequest.readyState == 4 && !statusAborted) {
         if (statusHttpRequest.status == 200) {
            // We have received a status response, all is well. Typically the first one will occur for 'session' which will respond
            // immediately so we can make a call on the viewer here to say/confirm that we are up and runnng.
            if (firstResponse) {           
               if (typeof(viewer) == 'object' && viewer.setConnected != undefined) 
                  viewer.setConnected(1);
               firstResponse = false;
            }   
            parseResponse(statusHttpRequest.responseText);
            statusFails = 0; // reset the fail counter
            statusRequest(); 
         }
         else if (statusHttpRequest.status != 403 && ++statusFails < 3) {
            // If the status request fails then try to re-make it. Timeouts with broken connection seem to take 3-4 s
            // A 403 will occur where the server has been reset and a status request occurs without a prior reload.
            console.log("Status request failed", statusHttpRequest.status);
            window.setTimeout(statusRequest, 1000); 
         }
         else {
            // Failed to reconnect - show an error:
            statusAbort();
            statusLost();
         } 
      }
   }; 
   statusHttpRequest.ontimeout = function () {
      // Normally, a timeout occurs where the connection to the appliance is still valid but there is no response; it can also
      // occur if the appliance has been turned off or gone out of wifi range. We count this situation as 3 fails in total. 
      // The readystate will go to 4=done after a timeout so the mechanism above will trigger and the host/viewer will be informed.
      statusAbort();
      statusLost();               
   };   
   if (statusRequests++ == 0)                 
      statusHttpRequest.open("GET", "session", true);
   else 
      statusHttpRequest.open("GET", "status", true);
   statusHttpRequest.send();
}
  
 
function postEvent (id, msg) { sendMessage ("POST", id, null, msg); }          
function postState (id, state, msg) { sendMessage ("POST", id, state, msg); }
function recordState (id, state, msg) { sendMessage ("PUT", id, state, msg); }
                  
// Transmit state change event - the new state will be recorded/preserved by the server
function sendMessage (action, id, state, msg) {
   var params = "";
   if (msg != undefined) {
      if (typeof(msg)!='object')
         msg = [ msg ];               
      for (var i in msg) { 
         if (typeof(msg[i]) === 'string')
            msg[i] = JSON.stringify(msg[i]);
         if (i > 0)
            params = params+',';   
         params = params + msg[i];
      }
   }
   
   if (state != null)                       
      messageQueue.push([action, id+"."+state+"="+params]);
   else
      messageQueue.push([action, id+"="+params]);                  
   if (messageQueue.length == 1)
      dispatchMessages();
}

// Attempt to dispatch any queued messages. 
// Messages are dispatched in order and in batches (of the same action type)
// enabling a fairly fast throughput even over a slow link.
function dispatchMessages () {                        
   if (messageQueue.length > 0) {
      var body = "";
      var msgCount = 0;
      var action = messageQueue[0][0];
      for (var i=0; i<messageQueue.length && messageQueue[i][0] == action; ++i) {
         body += messageQueue[i][1]+"\n";
         msgCount += 1;
      }
      body += "\n";   
      messageHttpRequest = new XMLHttpRequest();               
      messageHttpRequest.open(action, "event", true);
      messageHttpRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
      messageHttpRequest.timeout = 0;
      messageHttpRequest.onreadystatechange = function() {
         if (messageHttpRequest.readyState == 4 && !statusAborted) {
            if (messageHttpRequest.status == 200) 
               messageQueue.splice(0, msgCount);  // Success so remove messages
            dispatchMessages(); // Go again if messages are waiting.                                     
         }
      }
      messageHttpRequest.send(body);
   }
}

// Request a data or resource file from the server, then call a function when the request is complete.
function requestFile (filename, handler) {
   var xhttp = new XMLHttpRequest();
   xhttp.onreadystatechange = function() {
      if (xhttp.readyState == 4) {
         var text = (xhttp.status == 200) ? xhttp.responseText : null;
         handler(text);
      }
   }   
   
   xhttp.open("GET", "/"+filename, true);
   xhttp.send();             
}
      
function statusLost () {
   if (typeof(viewer) == "object" && viewer.setConnected != undefined) 
      viewer.setConnected(0);
   container.innerHTML = "<P class=\"error\">Lost connection to the '"+pageTitle+"'.</P>";                     
}

function statusAbort () {
   statusAborted = true;
   if (statusHttpRequest != null) 
      statusHttpRequest.abort()
   if (messageHttpRequest != null) 
      messageHttpRequest.abort()
}


