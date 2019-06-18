double TEST_pair_force(double r2, double* F_mod)
{
	FILE* fp;
	char filename2[64];
	double V = 0.0, r_2 = 0.0, k = 0.0;

	sprintf(filename2, "R2_FUERZA_V.txt");
	fp = fopen(filename2, "w");

	for(k = 0; k < 7; k = k+0.01)
	{
		r_2 = (float) (k+1);
		V = pair_force(r_2,F_mod);
		fprintf(fp,"%lf\t",r_2);
		fprintf(fp,"%lf\t",F_mod[0]);
		fprintf(fp,"%lf\n",V);
		F_mod[0] = 0.0; // lo restarteo cada vez
		printf("va por la iteracion %lf\n",k);
	}
	fclose(fp);
}