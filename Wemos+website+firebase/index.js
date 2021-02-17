firebase.database().ref('wemos').on("child_added",function(data){
   console.log(data.val());
   data.val().onChange=function(){
      console.log(data.val());

   }

   // var newData=data.val();
   // console.log("time:"+newData.Time);
   // console.log()
})
function servoMove(){
   var value=document.getElementById("points").value;
   var IntCon=parseInt(value);
   firebase.database().ref('wemos/servo').set(IntCon);
}
function changeLed(value){
   firebase.database().ref('wemos/led').set(value)
}
// var database = firebase.database().ref();
// var database = firebase.database();

// console.log()
// function changeLed(value){
//    firebase.database().ref('/wemos/').set({
//     led:1
//     });


//  }

//  function changeLed(value){
    // var getTitle=document.getElementById('title');
    // var getDetails=document.getElementById('details');
    // var getDate=document.getElementById('date');
    // var key=firebase.database().ref('todos').push().key;
    // var todo={
    //     getTitle:getTitle.value,
    //     getDetails:getDetails.value,
    //     getDate:getDate.value,
    //     key:key
    // }   
   // firebase.database().ref('wemos').child("led").set(value);
   // }

   window.onload = function () {

      var dps = []; // dataPoints
      var chart = new CanvasJS.Chart("chartContainer", {
         title :{
            text: "Dynamic Data"
         },
         data: [{
            type: "line",
            dataPoints: dps
         }]
      });
      
      var xVal = 0;
      var yVal = 100; 
      var updateInterval = 1000;
      var dataLength = 20; // number of dataPoints visible at any point
      
      var updateChart = function (count) {
      
         count = count || 1;
      
         for (var j = 0; j < count; j++) {
            yVal = yVal +  Math.round(5 + Math.random() *(-5-5));
            dps.push({
               x: xVal,
               y: yVal
            });
            xVal++;
         }
      
         if (dps.length > dataLength) {
            dps.shift();
         }
      
         chart.render();
      };
      
      updateChart(dataLength);
      setInterval(function(){updateChart()}, updateInterval);
      
      }