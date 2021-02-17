var database = firebase.database();
function changeLed(value){
    database.ref('wemos/').child("led").set(value);


 }

 function changeLed(value){
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
   firebase.database().ref('wemos').child("led").set(value);
   }