/*
  debug function for DGB
*/
void dummy(){int x=0;}
void pm(std::map<std::string,int32_t>& mymap){
    for (auto& x: mymap) {
    std::cout << x.first << ": " << x.second << '\n';
  }
}
