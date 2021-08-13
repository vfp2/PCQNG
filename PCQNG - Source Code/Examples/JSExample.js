// Load PCQNG control
var xPCQNG = new ActiveXObject("QWPCQNG.PCQNG");

// Open the PCQNG
xPCQNG.Open();

// Get random numbers
var Int32 = xPCQNG.RandInt32;
var Uniform = xPCQNG.RandUniform;
var Normal = xPCQNG.RandNormal;

// Show results in popup
WScript.Echo('Int32: ' + Int32.toString() + '\n' +
'Uniform: ' + Uniform.toString() + '\n' +
'Normal: ' + Normal.toString());

// Close PCQNG
xPCQNG.Close();