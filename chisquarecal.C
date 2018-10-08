{
  ifstream input("TabulatedvsCalculatedE.dat");
  double x, y, eX,eY,num,den,sum=0;
  while(1)
	{
	  input>>x>>y>>eX>>eY;
	  if(!input.good())break;
	  //  sum+=(x-y)*(x-y)/(eY*eY);
	  cout<<x<<'\t'<<y<<'\t'<<eX<<'\t'<<eY<<'\t'<<endl;
	  num=pow(x-y,2);
	  cout<<num<<endl;
	  den=pow(eX,2);
	  cout<<den<<endl;
	  //sum+=1.0*pow(x-y,2)/pow(eX,2);
	  sum+=num/den;
	  // cout<<"sum= "<<sum<<endl;
	}
  cout<<sum<<endl;
}
