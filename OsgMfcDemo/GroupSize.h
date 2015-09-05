#define FULLSIZE(winId,pad_l,pad_t,pad_r,pad_b){\
	RECT rect;\
	this->GetClientRect(&rect);\
	CWnd*win=GetDlgItem(winId);\
	if (win&&win->GetSafeHwnd())\
	{\
	   win->MoveWindow(pad_l,pad_t,rect.right-rect.left-pad_l-pad_r,rect.bottom-rect.top-pad_t-pad_b);\
	}\
}
#define GROUPSIZE(groupId,winId){\
	RECT rect;\
	this->GetClientRect(&rect);\
	CWnd*group=GetDlgItem(groupId);\
	if (group&&group->GetSafeHwnd())\
	{\
		group->MoveWindow(0,0,rect.right-rect.left,rect.bottom-rect.top);\
	}\
	CWnd*win=GetDlgItem(winId);\
	if (win&&win->GetSafeHwnd())\
	{\
		win->MoveWindow(10,15,rect.right-rect.left-20,rect.bottom-rect.top-20);\
	}\
}