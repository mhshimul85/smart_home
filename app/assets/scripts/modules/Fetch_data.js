import $ from 'jquery';

class Fetch_data {
    constructor() {
  $(document).ready(function(){
  // Defining Variable
  var relay_one;
  var relay_two;
  var relay_three;
  var relay_four;
  var tank;
  
  // Refresshing our code after 3 second
  var intId = setInterval(counter, 3000);
  // Code for load data from database and change switch status
  function counter() {
    $.get('https://besmart2020.000webhostapp.com/one/val.php')
      .done((data) => {
          console.log(data);
          relay_one = data['relay_one'];
          relay_two = data['relay_two'];
          relay_three = data['relay_three'];
          relay_four = data['relay_four'];
          tank = data['tank'];
          
          // Water level checker
          $('.water-tank-p').text(tank+"%");
          $('.water-tank-waterlevel').css("height", tank+"%");
          
          // Water level with color
          if( 0 <= tank && tank <= 20 ){
            $('.water-tank-waterlevel').css("background", "#ff0000");
          } else if( 20 < tank && tank <= 40) {
            $('.water-tank-waterlevel').css("background", "#ff66cc");
          } else if( 40 < tank && tank <= 60) {
            $('.water-tank-waterlevel').css("background", "#9900ff");
          } else if( 60 < tank && tank <= 80) {
            $('.water-tank-waterlevel').css("background", "#0080ff");
          } else if( 80 < tank && tank <= 100) {
            $('.water-tank-waterlevel').css("background", "#40ff00");
          } 

          // Relay switch mode changer
          if(relay_one == 1){
            $('.relay_one').attr('checked','checked');
          } else {
            $('.relay_one').removeAttr('checked');
          }
      
          if(relay_two == 1){
            $('.relay_two').attr('checked','checked');
          } else {
            $('.relay_two').removeAttr('checked');
          }
      
          if(relay_three == 1){
            $('.relay_three').attr('checked','checked');
          } else {
            $('.relay_three').removeAttr('checked');
          }
      
          if(relay_four == 1){
            $('.relay_four').attr('checked','checked');
          } else {
            $('.relay_four').removeAttr('checked');
          }

          // Check all output in console
          console.log(relay_one+' '+relay_two+' '+relay_three+' '+relay_four+' '+tank);
      })
      .fail((error) => console.error(error))
      .always(() => console.log('Done'));
  } 
  
  // Onclick changes button status 
  $('input').click(function(){
    var relay = $(this).attr('class');
    var values;
    var con;
    // Assigning the relays value to another variable
    switch (relay) {
      case 'relay_one':
        values = relay_one;
        break;
      case 'relay_two':
        values = relay_two; 
        break;
      case 'relay_three':
        values = relay_three;
        break;
      case 'relay_four':
        values = relay_four;
        break;
      default:;
    }
    // Updating the relay values
    if(values == 1){
      con = 'https://besmart2020.000webhostapp.com/one/update.php?relay='+relay+'&value=0';
      //window.location = 'http://besmart2020.000webhostapp.com/one/update.php?relay_one='+relayOne+'&relay_two='+relayTwo+'&relay_three='+relayThree+'&relay_four='+relayFour;
		} else {
      con = 'https://besmart2020.000webhostapp.com/one/update.php?relay='+relay+'&value=1';
    }
    $(".frame").attr("src", con);
    $('.frame').trigger('click');
  });
});

    }
}

export default Fetch_data;