// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   sha512.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: feedme <marvin@42.fr>                      +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/05/01 01:11:51 by feedme            #+#    #+#             */
// /*   Updated: 2019/05/01 01:11:59 by feedme           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "md5.h"

// int						find_len512(int len)
// {
// 	int				new;

// 	new = 128;
// 	while ((new - 16) <= len)
// 		new += 128;
// 	return (new);
// }

// unsigned char			*prepare_sha512(unsigned char *inp, int len)
// {
// 	unsigned char	*new;
// 	int				new_len;
// 	long double  		tmp2;

// 	new_len = find_len512(len);
// 	new = (unsigned char*)malloc(new_len);
// 	ft_bzero(new, new_len);
// 	new = ft_memcpy(new, inp, len);
// 	new[len] = 128;
// 	tmp2 = (len * 8);
// 	ft_memcpy(&new[new_len - 16], &tmp2, 16);
// 	return (new);
// }

// unsigned long			*create_k512(void)
// {
// 	static unsigned long	k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd,
// 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
// 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
// 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
// 0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
// 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
// 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210,
// 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
// 0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926,
// 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8,
// 0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
// 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 0xd69906245565a910,
// 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 
// 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
// 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60,
// 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9,
// 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
// 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 
// 0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493,
// 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
// 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

// 	return (k);
// }

// unsigned int	*init_sha512(t_sha *vars, unsigned char *inp)
// {
// 	unsigned char		*tmp;

// 	tmp = (unsigned char*)malloc(16);
// 	// vars->h0 = 0x6a09e667;
// 	// vars->h1 = 0xbb67ae85;
// 	// vars->h2 = 0x3c6ef372;
// 	// vars->h3 = 0xa54ff53a;
// 	// vars->h4 = 0x510e527f;
// 	// vars->h5 = 0x9b05688c;
// 	// vars->h6 = 0x1f83d9ab;
// 	// vars->h7 = 0x5be0cd19;
// 	vars->msg = prepare_sha512(inp, ft_strlen((char*)inp));
// 	vars->new_len = find_len512(ft_strlen((char*)inp));
// 	tmp = ft_memrev(tmp, vars->msg + vars->new_len - 16, 16);
// 	ft_memcpy(vars->msg + vars->new_len - 16, tmp, 16);
// 	free(tmp);
// 	return (create_k512());
// }

// unsigned char	*sha512(unsigned char *inp)
// {
// 	t_sha			vars;
// 	int				i;
// 	t_tmp			tmp;
// 	unsigned long	*k;

// 	i = 0;
// 	k = init_sha512(&vars, inp);
// 	while (i < vars.new_len)
// 	{
// 		build_tmp2(&vars, &tmp, vars.msg + i);
// 		update_vars(&tmp);
// 		vars.h0 = vars.h0 + tmp.a;
// 		vars.h1 = vars.h1 + tmp.b;
// 		vars.h2 = vars.h2 + tmp.c;
// 		vars.h3 = vars.h3 + tmp.d;
// 		vars.h4 = vars.h4 + tmp.e;
// 		vars.h5 = vars.h5 + tmp.f;
// 		vars.h6 = vars.h6 + tmp.g;
// 		vars.h7 = vars.h7 + tmp.h;
// 		i += 64;
// 	}
// 	free(vars.msg);
// 	return (sha_digest(vars));
// }