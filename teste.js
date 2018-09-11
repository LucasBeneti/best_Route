var lat1 = -25.4352976;
var lon1 = -49.27041;
var lat2 = -25.4777378;
var lon2 = -49.3292729;

Distancia = Dist(lat1, lon1, lat2, lon2); //Quilómetros de retorno

function Dist(lat1, lon1, lat2, lon2)
  {
  rad = function(x) {return x*Math.PI/180;}

  var R     = 6371137;                  //Raio da Terra no km (WGS84)
  var dLat  = rad( lat2 - lat1 );
  var dLong = rad( lon2 - lon1 );

  var a = Math.sin(dLat/2) * Math.sin(dLat/2) + Math.cos(rad(lat1)) * Math.cos(rad(lat2)) * Math.sin(dLong/2) * Math.sin(dLong/2);
  var c = 2 * Math.atan2(Math.sqrt(a), Math.sqrt(1-a));
  var d = R * c;

  return d;                   //Retorno 3 casas decimais
}
console.log(Distancia)
