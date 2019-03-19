#include "crocodile.h"

uint8 brev_5b(uint8 i) 
{
	uint8 o = 0x00; 
	o = o | (i & 0x01) << 4; 
	o = o | (i & 0x02) << 2; 
	o = o | (i & 0x04); 
	o = o | (i & 0x08) >> 2; 
	o = o | (i & 0x10) >> 4;

	return o;
}

uint8 brev_4b(uint8 i) 
{
	uint8 o = 0x00;
	o = o | (i & 0x01) << 3;
	o = o | (i & 0x02) << 1;
	o = o | (i & 0x04) >> 1;
	o = o | (i & 0x08) >> 3;

	return o;
}

crocodile::crocodile()
{
	clear();
}

crocodile::~crocodile()
{
}

void crocodile::clear()
{
	sr.clear(); 
	sr.push_back(0x00); sr.push_back(0x00); sr.push_back(0x62); sr.push_back(0x98);
	sr.push_back(0xA6); sr.push_back(0x49); sr.push_back(0x8A); sr.push_back(0x12);
	sr.push_back(0x12); sr.push_back(0x43); sr.push_back(0xFF);
}

void crocodile::mod_enable(croc_mod mod) 
{
	switch (mod) {
	case croc_mod_pp: sr[0] = sr[0] | 0x04; break;
	case croc_mod_sp: sr[0] = sr[0] | 0x02; break;
	case croc_mod_nd: sr[0] = sr[0] | 0x01; break;
	case croc_mod_hr: sr[1] = sr[1] | 0x80; break;
	case croc_mod_wh: sr[1] = sr[1] | 0x40; break;
	}
}

void crocodile::mod_disable(croc_mod mod)
{
	switch (mod) {
	case croc_mod_pp: sr[0] = sr[0] & ~0x04; break;
	case croc_mod_sp: sr[0] = sr[0] & ~0x02; break;
	case croc_mod_nd: sr[0] = sr[0] & ~0x01; break;
	case croc_mod_hr: sr[1] = sr[1] & ~0x80; break;
	case croc_mod_wh: sr[1] = sr[1] & ~0x40; break;
	}
}

void crocodile::mod_assert_reset(croc_mod mod)
{
	switch (mod) {
	case croc_mod_pp: sr[1] = sr[1] | 0x20; break;
	case croc_mod_sp: sr[1] = sr[1] | 0x10; break;
	case croc_mod_nd: sr[1] = sr[1] | 0x08; break;
	case croc_mod_hr: sr[1] = sr[1] | 0x04; break;
	case croc_mod_wh: sr[1] = sr[1] | 0x02; break;
	}
}

void crocodile::mod_deassert_reset(croc_mod mod)
{
	switch (mod) {
	case croc_mod_pp: sr[1] = sr[1] & ~0x20; break;
	case croc_mod_sp: sr[1] = sr[1] & ~0x10; break;
	case croc_mod_nd: sr[1] = sr[1] & ~0x08; break;
	case croc_mod_hr: sr[1] = sr[1] & ~0x04; break;
	case croc_mod_wh: sr[1] = sr[1] & ~0x02; break;
	}
}

void crocodile::mod_set_ph_ref_0(croc_mod mod, uint8 ph_ref)
{
	uint8 ph_ref_r = brev_5b(ph_ref);

	switch (mod)
	{
	case croc_mod_pp:
		sr[1] = sr[1] | (ph_ref_r & 0x10) >> 4;
		sr[2] = sr[2] | (ph_ref_r & 0x0F) << 4;
		break;
	case croc_mod_sp:
		sr[3] = sr[3] | ph_ref_r << 2;
		break;
	case croc_mod_nd:
		sr[4] = sr[4] | ph_ref_r;
		break;
	case croc_mod_hr:
		sr[5] = sr[5] | (ph_ref_r & 0x1C) >> 2;
		sr[6] = sr[6] | (ph_ref_r & 0x03) << 6;
		break;
	default:
		break;
	}
}

void crocodile::mod_set_ph_ref_1(croc_mod mod, uint8 ph_ref)
{
	uint8 ph_ref_r = brev_5b(ph_ref);

	switch (mod)
	{
	case croc_mod_pp:
		sr[2] = sr[2] | (ph_ref_r & 0x1E) >> 1;
		sr[3] = sr[3] | (ph_ref_r & 0x01) << 7;
		break;
	case croc_mod_sp:
		sr[3] = sr[3] | (ph_ref_r & 0x18) >> 3;
		sr[4] = sr[4] | (ph_ref_r & 0x07) << 5;
		break;
	case croc_mod_nd:
		sr[5] = sr[5] | ph_ref_r << 3;
		break;
	case croc_mod_hr:
		sr[6] = sr[6] | ph_ref_r << 1;
		break;
	default:
		break;
	}
}

void crocodile::mod_sel_clk(bool ext_clk) 
{
	if (ext_clk)
		sr[7] = sr[7] | 0x10;
	else
		sr[7] = sr[7] & ~0x10;
}

void crocodile::mod_set_wh_trim(uint8 wh_trim) 
{
	uint8 wh_trim_r = brev_4b(wh_trim);

	sr[6] = sr[6] | (wh_trim_r & 0x08) >> 3;
	sr[7] = sr[7] | (wh_trim_r & 0x07) << 5;
}

void crocodile::dco_enable() 
{ 
	sr[7] = sr[7] | 0x02; 
}

void crocodile::dco_disable() 
{ 
	sr[7] = sr[7] & ~0x02;
}

void crocodile::dco_set_cs(uint8 cs)
{
	uint8 cs_r = brev_5b(cs);

	sr[7] = sr[7] | (cs_r & 0x10) >> 4;
	sr[8] = sr[8] | (cs_r & 0x0F) << 4 ;

}

void crocodile::dco_set_fil_cs(uint8 fil_cs)
{
	uint8 fil_cs_r = brev_5b(fil_cs);

	sr[9] = sr[9] | (fil_cs_r & 0x18) >> 3;
	sr[10] = sr[10] | (fil_cs_r & 0x07) << 5;

}

void crocodile::dco_set_fil_fn(uint8 fil_fn)
{
	uint8 fil_fn_r = brev_5b(fil_fn);

	sr[10] = sr[10] | fil_fn_r;
}
