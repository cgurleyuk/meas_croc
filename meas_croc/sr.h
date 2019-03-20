#pragma once

typedef unsigned char uint8;

#include <vector>

enum croc_mod 
{
	croc_mod_pp,
	croc_mod_sp,
	croc_mod_nd,
	croc_mod_hr,
	croc_mod_wh
};

class sr
{
	std::vector<uint8> vsr;
public:
	sr();
	~sr();

	void clear();

	void mod_enable(croc_mod mod);
	void mod_disable(croc_mod mod);
	void mod_assert_reset(croc_mod mod);
	void mod_deassert_reset(croc_mod mod);
	void mod_set_ph_ref_0(croc_mod mod, uint8 ph_ref);
	void mod_set_ph_ref_1(croc_mod mod, uint8 ph_ref);
	void mod_sel_clk(bool extClk);
	void mod_set_wh_trim(uint8 wh_trim);

	void dco_enable();
	void dco_disable();
	void dco_set_cs(uint8 cs);
	void dco_set_fil_cs(uint8 fil_cs);
	void dco_set_fil_fn(uint8 fil_fn);

	std::vector<uint8> get_sr() { return vsr; };
};
