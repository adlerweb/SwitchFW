uint64_t hexatoi(char *in){
  uint64_t value=0;
  unsigned char i=0;
  while(1){
    if(in[i] >= '0' && in[i] <= '9'){
      value <<= 4;
      value |= in[i] - '0';
    }
    else if(in[i] >= 'A' && in[i] <= 'F'){
      value <<= 4;
      value |= in[i] - 'A'+10;
    }
      else if(in[i] >= 'a' && in[i] <= 'f'){
      value <<= 4;
      value |= in[i] - 'a'+10;
    }
    else
      break;
    i++;
  }
  return value;
}