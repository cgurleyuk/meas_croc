#include "sr.h"

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

sr::sr()
{
	clear();
}

sr::~sr()
{
}

void sr::clear()
{
	vsr.clear(); 
	vsr.push_back(0x00); vsr.push_back(0x00); vsr.push_back(0x62); vsr.push_back(0x98);
	vsr.push_back(0xA6); vsr.push_back(0x49); vsr.push_back(0x8A); vsr.push_back(0x12);
	vsr.push_back(0x12); vsr.push_back(0x43); vsr.push_back(0xFF);
}

void sr::mod_enable(sr_mod mod) 
{
	switch (mod) {
	case sr_mod_pp: vsr[0] = vsr[0] | 0x04; break;
	case sr_mod_sp: vsr[0] = vsr[0] | 0x02; break;
	case sr_mod_nd: vsr[0] = vsr[0] | 0x01; break;
	case sr_mod_hr: vsr[1] = vsr[1] | 0x80; break;
	case sr_mod_wh: vsr[1] = vsr[1] | 0x40; break;
	}
}

void sr::mod_disable(sr_mod mod)
{
	switch (mod) {
	case sr_mod_pp: vsr[0] = vsr[0] & ~0x04; break;
	case sr_mod_sp: vsr[0] = vsr[0] & ~0x02; break;
	case sr_mod_nd: vsr[0] = vsr[0] & ~0x01; break;
	case sr_mod_hr: vsr[1] = vsr[1] & ~0x80; break;
	case sr_mod_wh: vsr[1] = vsr[1] & ~0x40; break;
	}
}

void sr::mod_assert_reset(sr_mod mod)
{
	switch (mod) {
	case sr_mod_pp: vsr[1] = vsr[1] | 0x20; break;
	case sr_mod_sp: vsr[1] = vsr[1] | 0x10; break;
	case sr_mod_nd: vsr[1] = vsr[1] | 0x08; break;
	case sr_mod_hr: vsr[1] = vsr[1] | 0x04; break;
	case sr_mod_wh: vsr[1] = vsr[1] | 0x02; break;
	}
}

void sr::mod_deassert_reset(sr_mod mod)
{
	switch (mod) {
	case sr_mod_pp: vsr[1] = vsr[1] & ~0x20; break;
	case sr_mod_sp: vsr[1] = vsr[1] & ~0x10; break;
	case sr_mod_nd: vsr[1] = vsr[1] & ~0x08; break;
	case sr_mod_hr: vsr[1] = vsr[1] & ~0x04; break;
	case sr_mod_wh: vsr[1] = vsr[1] & ~0x02; break;
	}
}

void sr::mod_set_ph_ref_0(sr_mod mod, uint8 ph_ref)
{
	uint8 ph_ref_r = brev_5b(ph_ref);

	switch (mod)
	{
	case sr_mod_pp:
		vsr[1] = vsr[1] | (ph_ref_r & 0x10) >> 4;
		vsr[2] = vsr[2] | (ph_ref_r & 0x0F) << 4;
		break;
	case sr_mod_sp:
		vsr[3] = vsr[3] | ph_ref_r << 2;
		break;
	case sr_mod_nd:
		vsr[4] = vsr[4] | ph_ref_r;
		break;
	case sr_mod_hr:
		vsr[5] = vsr[5] | (ph_ref_r & 0x1C) >> 2;
		vsr[6] = vsr[6] | (ph_ref_r & 0x03) << 6;
		break;
	default:
		break;
	}
}

void sr::mod_set_ph_ref_1(sr_mod mod, uint8 ph_ref)
{
	uint8 ph_ref_r = brev_5b(ph_ref);

	switch (mod)
	{
	case sr_mod_pp:
		vsr[2] = vsr[2] | (ph_ref_r & 0x1E) >> 1;
		vsr[3] = vsr[3] | (ph_ref_r & 0x01) << 7;
		break;
	case sr_mod_sp:
		vsr[3] = vsr[3] | (ph_ref_r & 0x18) >> 3;
		vsr[4] = vsr[4] | (ph_ref_r & 0x07) << 5;
		break;
	case sr_mod_nd:
		vsr[5] = vsr[5] | ph_ref_r << 3;
		break;
	case sr_mod_hr:
		vsr[6] = vsr[6] | ph_ref_r << 1;
		break;
	default:
		break;
	}
}

void sr::mod_sel_clk(bool ext_clk) 
{
	if (ext_clk)
		vsr[7] = vsr[7] | 0x10;
	else
		vsr[7] = vsr[7] & ~0x10;
}

void sr::mod_set_wh_trim(uint8 wh_trim) 
{
	uint8 wh_trim_r = brev_4b(wh_trim);

	vsr[6] = vsr[6] | (wh_trim_r & 0x08) >> 3;
	vsr[7] = vsr[7] | (wh_trim_r & 0x07) << 5;
}

void sr::dco_enable() 
{ 
	vsr[7] = vsr[7] & ~0x02;
}

void sr::dco_disable() 
{ 
	vsr[7] = vsr[7] | 0x02;
}

void sr::dco_set_cs(uint8 cs)
{
	uint8 cs_r = brev_5b(cs);

	vsr[7] = vsr[7] | (cs_r & 0x10) >> 4;
	vsr[8] = vsr[8] | (cs_r & 0x0F) << 4 ;

}

void sr::dco_set_fil_cs(uint8 fil_cs)
{
	uint8 fil_cs_r = brev_5b(fil_cs);

	vsr[9] = vsr[9] | (fil_cs_r & 0x18) >> 3;
	vsr[10] = vsr[10] | (fil_cs_r & 0x07) << 5;

}

void sr::dco_set_fil_fn(uint8 fil_fn)
{
	uint8 fil_fn_r = brev_5b(fil_fn);

	vsr[10] = vsr[10] | fil_fn_r;
}

void sr::sel_bsa(sr_sel_bsa sel_bsa)
{
	switch (sel_bsa)
	{
	case sr_sel_bsa_pp:
		vsr[8] = vsr[8] & 0xF3;
		break;
	case sr_sel_bsa_sp:
		vsr[8] = vsr[8] & 0xF3;
		vsr[8] = vsr[8] | 0x08;
		break;
	case sr_sel_bsa_nd:
		vsr[8] = vsr[8] & 0xF3;
		vsr[8] = vsr[8] | 0x04;
		break;
	case sr_sel_bsa_hr:
		vsr[8] = vsr[8] & 0xF3;
		vsr[8] = vsr[8] | 0x0C;
		break;
	default:
		break;
	}
}

void sr::sel_bsb(sr_sel_bsb sel_bsb)
{
	switch (sel_bsb)
	{
	case sr_sel_bsb_pp:
		vsr[8] = vsr[8] & 0xFC;
		break;
	case sr_sel_bsb_sp:
		vsr[8] = vsr[8] & 0xFC;
		vsr[8] = vsr[8] | 0x02;
		break;
	case sr_sel_bsb_nd:
		vsr[8] = vsr[8] & 0xFC;
		vsr[8] = vsr[8] | 0x01;
		break;
	case sr_sel_bsb_hr:
		vsr[8] = vsr[8] & 0xFC;
		vsr[8] = vsr[8] | 0x03;
		break;
	default:
		break;
	}
}

void sr::sel_bsc(sr_sel_bsc sel_bsc)
{
	switch (sel_bsc)
	{
	case sr_sel_bsc_pp:
		vsr[9] = vsr[9] & 0x3F;
		break;
	case sr_sel_bsc_sp:
		vsr[9] = vsr[9] & 0x3F;
		vsr[9] = vsr[9] | 0x80;
		break;
	case sr_sel_bsc_wh:
		vsr[9] = vsr[9] & 0x3F;
		vsr[9] = vsr[9] | 0x40;
		break;
	case sr_sel_bsc_hr:
		vsr[9] = vsr[9] & 0x3F;
		vsr[9] = vsr[9] | 0xC0;
		break;
	default:
		break;
	}
}
