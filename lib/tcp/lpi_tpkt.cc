/*
 *
 * Copyright (c) 2011-2016 The University of Waikato, Hamilton, New Zealand.
 * All rights reserved.
 *
 * This file is part of libprotoident.
 *
 * This code has been developed by the University of Waikato WAND
 * research group. For further information please see http://www.wand.net.nz/
 *
 * libprotoident is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libprotoident is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 */

#include <string.h>

#include "libprotoident.h"
#include "proto_manager.h"
#include "proto_common.h"

/* TPKT is a slightly annoying little protocol that is used by a variety of
 * applications. It is most notably used for RDP, but is also important for
 * anything based on the H.323 standard for multimedia conferencing (e.g.
 * Cisco CallManager).
 *
 * Basically, this module is going to be aimed at matching any generic
 * TPKT traffic that isn't something we can assign to a more specific
 * application, e.g. RDP
 */

static inline bool match_tpkt_generic(lpi_data_t *data, lpi_module_t *mod UNUSED) {

	if (match_tpkt(data->payload[0], data->payload_len[0])) {
		if (match_tpkt(data->payload[1], data->payload_len[1]))
			return true;
	}

	return false;
}

static lpi_module_t lpi_tpkt_generic = {
	LPI_PROTO_TPKT,
	LPI_CATEGORY_VOIP, /* Most TPKT stuff is for VOIP, conferencing etc */
	"TPKT",
	8,	/* Must come after RDP and S7COMM but before RTMP */
	match_tpkt_generic
};

void register_tpkt_generic(LPIModuleMap *mod_map) {
	register_protocol(&lpi_tpkt_generic, mod_map);
}

