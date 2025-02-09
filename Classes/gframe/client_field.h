#ifndef CLIENT_FIELD_H
#define CLIENT_FIELD_H

#include "config.h"
#include "../ocgcore/mtrandom.h"
#include <vector>
#include <set>
#include <map>
#ifdef _IRR_ANDROID_PLATFORM_
#include <android/TouchEventTransferAndroid.h>
#endif

namespace ygo {

class ClientCard;

struct ChainInfo {
	irr::core::vector3df chain_pos;
	ClientCard* chain_card;
	int code;
	int desc;
	int controler;
	int location;
	int sequence;
	bool solved;
	bool need_distinguish;
	std::set<ClientCard*> target;
};

class ClientField: public irr::IEventReceiver {
public:
	std::vector<ClientCard*> deck[2];
	std::vector<ClientCard*> hand[2];
	std::vector<ClientCard*> mzone[2];
	std::vector<ClientCard*> szone[2];
	std::vector<ClientCard*> grave[2];
	std::vector<ClientCard*> remove[2];
	std::vector<ClientCard*> extra[2];
	std::set<ClientCard*> overlay_cards;
	std::vector<ClientCard*> summonable_cards;
	std::vector<ClientCard*> spsummonable_cards;
	std::vector<ClientCard*> msetable_cards;
	std::vector<ClientCard*> ssetable_cards;
	std::vector<ClientCard*> reposable_cards;
	std::vector<ClientCard*> activatable_cards;
	std::vector<ClientCard*> attackable_cards;
	std::vector<ClientCard*> conti_cards;
	std::vector<std::pair<int,int>> activatable_descs;
	std::vector<int> select_options;
	std::vector<int> select_options_index;
	std::vector<ChainInfo> chains;
	int extra_p_count[2];

	size_t selected_option;
	ClientCard* attacker;
	ClientCard* attack_target;
	unsigned int disabled_field;
	unsigned int selectable_field;
	unsigned int selected_field;
	int select_min;
	int select_max;
	int must_select_count;
	int select_sumval;
	int select_mode;
	bool select_cancelable;
	bool select_panalmode;
	bool select_ready;
	int announce_count;
	int select_counter_count;
	int select_counter_type;
	std::vector<ClientCard*> selectable_cards;
	std::vector<ClientCard*> selected_cards;
	std::set<ClientCard*> selectsum_cards;
	std::vector<ClientCard*> selectsum_all;
	std::vector<int> declare_opcodes;
	std::vector<ClientCard*> display_cards;
	std::vector<int> sort_list;
	std::map<int, int> player_desc_hints[2];
	bool grave_act;
	bool remove_act;
	bool deck_act;
	bool extra_act;
	bool pzone_act[2];
	bool conti_act;
	bool chain_forced;
	ChainInfo current_chain;
	bool last_chain;
	bool deck_reversed;
	bool conti_selecting;
	bool cant_check_grave;
	mt19937 rnd;

	ClientField();
	void Clear();
	void Initial(int player, int deckc, int extrac);
	ClientCard* GetCard(int controler, int location, int sequence, int sub_seq = 0);
	void AddCard(ClientCard* pcard, int controler, int location, int sequence);
	ClientCard* RemoveCard(int controler, int location, int sequence);
	void UpdateCard(int controler, int location, int sequence, char* data);
	void UpdateFieldCard(int controler, int location, char* data);
	void ClearCommandFlag();
	void ClearSelect();
	void ClearChainSelect();
	void ShowSelectCard(bool buttonok = false, bool chain = false);
	void ShowChainCard();
	void ShowLocationCard();
	void ShowSelectOption(int select_hint = 0);
	void ReplaySwap();
	void RefreshAllCards();

	void GetChainLocation(int controler, int location, int sequence, irr::core::vector3df* t);
	void GetCardLocation(ClientCard* pcard, irr::core::vector3df* t, irr::core::vector3df* r, bool setTrans = false);
	void MoveCard(ClientCard* pcard, int frame);
	void FadeCard(ClientCard* pcard, int alpha, int frame);
	bool ShowSelectSum(bool panelmode);
	bool CheckSelectSum();
	bool CheckSelectTribute();
	bool check_min(const std::set<ClientCard*>& left, std::set<ClientCard*>::const_iterator index, int min, int max);
	bool check_sel_sum_s(const std::set<ClientCard*>& left, int index, int acc);
	void check_sel_sum_t(const std::set<ClientCard*>& left, int acc);
	bool check_sum(std::set<ClientCard*>::const_iterator index, std::set<ClientCard*>::const_iterator end, int acc, int count);
	bool check_sel_sum_trib_s(const std::set<ClientCard*>& left, int index, int acc);
	void check_sel_sum_trib_t(const std::set<ClientCard*>& left, int acc);
	bool check_sum_trib(std::set<ClientCard*>::const_iterator index, std::set<ClientCard*>::const_iterator end, int acc);

	void UpdateDeclarableList();
	void RefreshCardCountDisplay();

	irr::gui::IGUIElement* panel;
	bool is_dragging_cardtext;
	bool is_dragging_lstLog;
	bool is_dragging_lstReplayList;
	bool is_dragging_lstSinglePlayList;
	bool is_dragging_lstBotList;
	bool is_dragging_lstDecks;
	bool is_dragging_lstANCard;
    bool is_selectable;
    int dragging_tab_start_pos;
	int dragging_tab_start_y;
    std::vector<int> ancard;
	int hovered_controler;
	int hovered_location;
	size_t hovered_sequence;
	int command_controler;
	int command_location;
	size_t command_sequence;
	ClientCard* hovered_card;
	int hovered_player;
	ClientCard* clicked_card;
	ClientCard* command_card;
	ClientCard* highlighting_card;
	ClientCard* menu_card;
	int list_command;

	virtual bool OnEvent(const irr::SEvent& event);
	virtual bool OnCommonEvent(const irr::SEvent& event);
	void GetHoverField(int x, int y);
	void ShowMenu(int flag, int x, int y);
	void UpdateChainButtons();
	void ShowCancelOrFinishButton(int buttonOp);
	void SetShowMark(ClientCard* pcard, bool enable);
	void ShowCardInfoInList(ClientCard* pcard, irr::gui::IGUIElement* element, irr::gui::IGUIElement* parent);
	void SetResponseSelectedCards() const;
	void SetResponseSelectedOption() const;
	void CancelOrFinish();
};

}

//special cards
#define CARD_MARINE_DOLPHIN	78734254
#define CARD_TWINKLE_MOSS	13857930
#define CARD_QUESTION		38723936

#endif //CLIENT_FIELD_H
