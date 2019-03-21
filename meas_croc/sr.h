#pragma once

typedef unsigned char uint8;

#include <vector>

enum sr_mod 
{
	sr_mod_pp,
	sr_mod_sp,
	sr_mod_nd,
	sr_mod_hr,
	sr_mod_wh
};

enum sr_sel_bsa
{
	sr_sel_bsa_pp,
	sr_sel_bsa_sp,
	sr_sel_bsa_nd,
	sr_sel_bsa_hr
};

enum sr_sel_bsb
{
	sr_sel_bsb_pp,
	sr_sel_bsb_sp,
	sr_sel_bsb_nd,
	sr_sel_bsb_hr
};

enum sr_sel_bsc
{
	sr_sel_bsc_pp,
	sr_sel_bsc_sp,
	sr_sel_bsc_wh,
	sr_sel_bsc_hr
};

class sr
{
	std::vector<uint8> vsr;
public:
	sr();
	~sr();

	void clear();

	void mod_enable(sr_mod mod);
	void mod_disable(sr_mod mod);
	void mod_assert_reset(sr_mod mod);
	void mod_deassert_reset(sr_mod mod);
	void mod_set_ph_ref_0(sr_mod mod, uint8 ph_ref);
	void mod_set_ph_ref_1(sr_mod mod, uint8 ph_ref);
	void mod_sel_clk(bool extClk);
	void mod_set_wh_trim(uint8 wh_trim);

	void sel_bsa(sr_sel_bsa sel_bsa);
	void sel_bsb(sr_sel_bsb sel_bsb);
	void sel_bsc(sr_sel_bsc sel_bsc);

	void dco_enable();
	void dco_disable();
	void dco_set_cs(uint8 cs);
	void dco_set_fil_cs(uint8 fil_cs);
	void dco_set_fil_fn(uint8 fil_fn);

	std::vector<uint8> get_vsr() { return vsr; };
};
