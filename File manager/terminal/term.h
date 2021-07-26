#ifndef _SAVE_TERM_H_
#define _SAVE_TERM_H_

//вызов только один раз в начале программы
int TermSaveDefault(void);

int TermStoreDefault(void);

//вызов только один раз, после настройки ncurses
int TermSaveMyConf(void);

int TermStoreMyConf(void);


#endif //_SAVE_TERM_H_