/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testfelsprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-fram <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:43:56 by fde-fram          #+#    #+#             */
/*   Updated: 2020/01/21 16:30:48 by fde-fram         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	recurs2(int i, float valeury, t_data *d, float *joueur, float stocke);
void	recurs3(int i, float valeury, t_data *d, float *joueur, float stocke);

int		balance_ray(t_data *d, int i, char *type)
{
	float pos[2];

	pos[i] = d->montan[2 + i] > 0 ? floor(d->joueur[i] + 1) :
		ceil(d->joueur[i] - 1);
	pos[!i] = (pos[i] - d->joueur[i]) * (d->montan[i]) + d->joueur[!i];
	pos[i] -= (pos[i] < d->joueur[i]);
	while (ab(pos[!i] - d->joueur[!i]) < ab(d->distmax[!i] - d->joueur[!i]) &&
	pos[0] < d->largs[0] && pos[0] >= 0 && pos[1] < d->largs[1] && pos[1] >= 0)
	{
		if (d->lmurs[(int)pos[0]][(int)pos[1]] != '0')
		{
			d->distmax[i] = pos[i] + (pos[i] < d->joueur[i]);
			d->distmax[!i] = pos[!i];
			*type = d->lmurs[(int)pos[0]][(int)pos[1]];
			return (1);
		}
		pos[i] += (d->montan[2 + i] > 0) ? 1 : -1;
		pos[!i] += (d->montan[2 + i] > 0) ? d->montan[i] : -d->montan[i];
	}
	return (0);
}

void	type1(int l, int i, t_data *d, float stocke)
{
	int		j;
	int		fin;
	float	newtaille;
	int		numtext;

	numtext = (d->distmax[l] > d->joueur[l]) + 2 * l;
	newtaille = d->h / 4 * sqrt((1 + pow(d->montan[0], 2))
			/ (pow(d->distmax[0] - d->joueur[0], 2)
				+ pow(d->distmax[1] - d->joueur[1], 2) + stocke))
		/ ab(d->cosdevie + d->sindevie * d->montan[0]);
	fin = d->h / 2 + newtaille;
	fin = fin > d->h ? d->h : fin;
	j = 0;
	while (j <= d->h / 2 - newtaille)
		d->data.addr[i + (j++) * (int)d->w] = d->coulpla;
	while (j < fin)
	{
		d->data.addr[i + j * (int)d->w] = d->data.text[numtext][(int)
		((j - d->h / 2 + newtaille) / (2 * newtaille) * d->data.wimg[numtext])
		+ d->data.wimg[numtext] * (int)(d->data.himg[numtext] *
		((d->distmax[!l]) - (int)(d->distmax[!l])))];
		j++;
	}
	while (j < d->h)
		d->data.addr[i + (j++) * (int)d->w] = d->coulsol;
}

void	type3(int l, int i, float valeury, t_data *d, float stocke)
{
	int		j;
	int		fin;
	float	newtaille;
	int		numtext;
	float		joueur[2];
	int cote = 0;
	numtext = (d->distmax[l] > d->joueur[l]) + 2 * l;
	newtaille = d->h / 4 * sqrt((1 + pow(d->montan[0], 2))
			/ (pow(d->distmax[0] - d->joueur[0], 2)
				+ pow(d->distmax[1] - d->joueur[1], 2) + stocke) )
		/ ab(d->cosdevie + d->sindevie * d->montan[0]);
	if (newtaille < 1)
		return;

	if(numtext < 1)
	{
		j = -1;
			joueur[0] = d->joueur[0];
			joueur[1] = d->joueur[1];
			//d->joueur[0] = d->distmax[0];
			d->joueur[0] = d->distmax[0] + 3;
			d->joueur[1] = d->distmax[1];//c + 3;
			if (((d->distmax[1]) - (int)(d->distmax[1])) < 0.01 || ((d->distmax[1]) - (int)(d->distmax[1])) > 0.99)
				cote = 1;

				stocke += pow(d->distmax[0] - joueur[0], 2) + pow(d->distmax[1] - joueur[1], 2);
		recurs3(i, valeury, d, joueur, stocke);
	}

	fin = d->h / 2 + newtaille;
	fin = fin > d->h ? d->h : fin;
	j = 0;
	while (j <= d->h / 2 - newtaille)
		d->data.addr[i + (j++) * (int)d->w] = d->coulpla;
	if(numtext >= 1)
	{
		while (j < fin)
		{
			d->data.addr[i + j * (int)d->w] = d->data.text[numtext][(int)
			((j - d->h / 2 + newtaille) / (2 * newtaille) * d->data.wimg[numtext])
			+ d->data.wimg[numtext] * (int)(d->data.himg[numtext] *
			((d->distmax[!l]) - (int)(d->distmax[!l])))];
			j++;
		}
	}
	else
	{
		if (cote)
		{
			while (j < fin)
			{
				d->data.addr[i + j * (int)d->w] = 123;
				j++;
			}
		}
		else
		{
			d->data.addr[i + j * (int)d->w] = 123;
			d->data.addr[i + (j+1) * (int)d->w] = 123;
			d->data.addr[i + (j+2) * (int)d->w] = 123;
			j = fin;
			d->data.addr[i + j * (int)d->w] = 123;
			d->data.addr[i + (j-1) * (int)d->w] = 123;
			d->data.addr[i + (j-2) * (int)d->w] = 123;
			j = fin;
		}
	}
	while (j < d->h)
		d->data.addr[i + (j++) * (int)d->w] = d->coulsol;
}

void	type2(int l, int i, float valeury, t_data *d, float stocke)
{
	float		dim[2];
	float		newtaille;
	float		newtaille2;
	float		joueur[2];
	int			j;
	j = -1;
	while (++j < 2)
	{
		dim[j] = (int)((d->distmax[j]) - ((j == l) && ((d->distmax[j]) <
		d->joueur[j]))) + 0.5 - d->joueur[j];
		joueur[j] = d->joueur[j];
		d->joueur[j] = d->distmax[j];
	}
	newtaille2 = 1 / sqrt(pow(dim[0], 2) + pow(dim[1], 2));
	newtaille = d->h / 3 / sqrt(pow(dim[0], 2) + pow(dim[1], 2) + stocke);
	recurs2(i, valeury, d, joueur, stocke);
	dim[0] = dim[1] / dim[0];
	if ((valeury = (((valeury - (dim[0] - d->tandevie) /
	(1 + dim[0] * d->tandevie))) / newtaille2)) <= -0.2 || valeury >= 0.2)
		return ;
	newtaille2 *= d->h / 3;
	j = d->h / 2;
	while (++j < d->h / 2 + newtaille && j < d->h)
		d->data.addr[i + j * (int)d->w] = d->data.text[4][(int)((j - d->h / 2)
	/ (newtaille) * d->data.wimg[4]) + d->data.wimg[4] * (int)((valeury + 0.2)
	/ 0.4 * d->data.himg[4])];
}

void	recurs2(int i, float valeury, t_data *d, float *joueur, float stocke)
{
	int		l;
	char	type;
	d->distmax[0] = 1000000.;
	d->distmax[1] = 1000000.;

	balance_ray(d, 0, &type);
	l = balance_ray(d, 1, &type);
	d->joueur[0] = joueur[0];
	d->joueur[1] = joueur[1];
	if (type == '2')
		type2(l, i, valeury, d, stocke);
	if (type == '1')
		type1(l, i, d, stocke);
	else if (type == '3')
		type3(l, i, valeury, d, stocke);

}

void	recurs3(int i, float valeury, t_data *d, float *joueur, float stocke)
{
	int		l;
	char	type;
	d->distmax[0] = 1000000.;
	d->distmax[1] = 1000000.;
	balance_ray(d, 0, &type);
	l = balance_ray(d, 1, &type);
	if (type == '1')
	{
		type1(l, i, d, stocke);
	}
	else if (type == '2')
	{
		type2(l, i, valeury, d, stocke);
	}
	else if (type == '3')
		type3(l, i, valeury, d, stocke);
	d->joueur[0] = joueur[0];
	d->joueur[1] = joueur[1];
}


int		print_screen(t_data *d)
{
	int		i;
	float	pas;
	float	valeury;

	i = 1;
	pas = 2 / d->w;
	valeury = -1 + pas;
	d->montan[2] = (d->cosdevie - d->sindevie * valeury);
	d->montan[3] = (d->cosdevie * valeury + d->sindevie);
	while (i < d->w)
	{
		d->montan[0] = (valeury + d->tandevie) / (1 - valeury * d->tandevie);
		d->montan[1] = 1 / d->montan[0];
		recurs3(i++, valeury, d, d->joueur, 0);
		valeury += pas;
		d->montan[2] -= pas * d->sindevie;
		d->montan[3] += pas * d->cosdevie;
	}
	mlx_put_image_to_window(d->data.mlx_ptr, d->data.mlx_win,
	d->data.mlx_img, 0, 0);
	return (0);
}
