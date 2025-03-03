/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_endian.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mifelida <mifelida@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 20:00:21 by mifelida          #+#    #+#             */
/*   Updated: 2025/03/03 20:23:37 by mifelida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_ENDIAN_H
# define CHECK_ENDIAN_H
# if defined (__BYTE_ORDER__) && defined (__ORDER_LITTLE_ENDIAN__)\
	&& defined (__ORDER_BIG_ENDIAN__)
#  if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#   define IS_LITTLE_ENDIAN 1
#  elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#   define IS_LITTLE_ENDIAN 0
#  else
#   error "Unknown byte order"
#  endif
# define IS_BIG_ENDIAN !(IS_LITTLE_ENDIAN)
# else
#  error "Unknown byte order"
# endif // defined (__BYTE_ORDER__) && defined (__ORDER_LITTLE_ENDIAN__)
	   // && defined (__ORDER_BIG_ENDIAN__)

#endif // !CHECK_ENDIAN_H

