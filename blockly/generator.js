javascript.javascriptGenerator.forBlock['open_gate_with_speed'] = function(block) {

  const speed = block.getFieldValue('SPEED');

  const code = `servo.write(90); // Speed: ${speed}\n`;

  return code;
};
