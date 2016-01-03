#include <string>
#include <unordered_map>

#include "SDL.h"

#include "DebugText.h"
#include "KeyboardEntry.h"
#include "TextInput.h"

KeyboardEntry::KeyboardEntry()
{
	isshift_ = false;
	isctrl_ = false;
	currentime_ = ENGLISH;
	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";

	hiraganamap_ = std::unordered_map<std::string, std::string>({
		{ "sh",  u8"しゃ" },
		{ "",  u8"" },
	});
}

KeyboardEntry::~KeyboardEntry()
{
	if (currenttexttexture_ != NULL)
	{
		FinalizeCurrentText();
		currenttexttexture_ = NULL;
	}

	currenttext_ = "";
	tempstring_ = "";
	nexttempchar_ = "";
}

void KeyboardEntry::InsertCharacter(char character)
{
	if (character >= 'a' && character <= 'z' && isshift_ == true)
	{
		currenttext_ = currenttext_ + static_cast<char>(character - 32);
	}
	else
	{
		if (isshift_ == true)
		{
			switch (character)
			{
			case '0':
				currenttext_ = currenttext_ + ')';
				break;
			case '1':
				currenttext_ = currenttext_ + '!';
				break;
			case '2':
				currenttext_ = currenttext_ + '@';
				break;
			case '3':
				currenttext_ = currenttext_ + '#';
				break;
			case '4':
				currenttext_ = currenttext_ + '$';
				break;
			case '5':
				currenttext_ = currenttext_ + '%';
				break;
			case '6':
				currenttext_ = currenttext_ + '^';
				break;
			case '7':
				currenttext_ = currenttext_ + '&';
				break;
			case '8':
				currenttext_ = currenttext_ + '*';
				break;
			case '9':
				currenttext_ = currenttext_ + '(';
				break;
			case '/':
				currenttext_ = currenttext_ + '?';
				break;
			}
		}
		else
		{
			currenttext_ = currenttext_ + character;
		}
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::InsertString(std::string string)
{
	currenttext_ = currenttext_ + string;

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::DeleteCharacter()
{
	if (currenttext_ != "")
	{
		currenttext_.pop_back();
	}

	if (currenttexttexture_ != NULL)
		if (tempstring_ == "" && nexttempchar_ == "")
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
		else
			currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
}

void KeyboardEntry::SetTexture(TextInput *text)
{
	FinalizeCurrentText();

	currenttexttexture_ = text;
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateQuickTextureFromText("|");
}

void KeyboardEntry::SetShift(bool isdown)
{
	isshift_ = isdown;
}

void KeyboardEntry::SetCTRL(bool isdown)
{
	isctrl_ = isdown;
}

void KeyboardEntry::FinalizeCurrentText()
{
	if (currenttexttexture_ != NULL)
		currenttexttexture_->CreateTextureFromText(currenttext_);

	currenttext_ = "";
	tempstring_ = "";
}

int KeyboardEntry::KeyDownInput(const SDL_Event &e)
{
	char chartoadd = 0;

	if (isctrl_ != true)
	{
		switch (currentime_)
		{
		case ENGLISH:
			chartoadd = KeyDownInputEnglish(e);

			if (chartoadd != 0)
				InsertCharacter(chartoadd);
			break;
		case JAPANESE:
			if (isshift_ == false)
				KeyDownInputJapaneseHiragana(e);
			else
				KeyDownInputJapaneseKatakana(e);

			if (currenttexttexture_ != NULL)
				if (tempstring_ == "" && nexttempchar_ == "")
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
				else
					currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '[' + tempstring_ + nexttempchar_ + ']');
			break;
		}

		switch (e.key.keysym.sym)
		{
		case SDLK_PERIOD:
			InsertCharacter('.');
			break;
		case SDLK_SLASH:
			InsertCharacter('/');
			break;
		case SDLK_0:
			InsertCharacter('0');
			break;
		case SDLK_1:
			InsertCharacter('1');
			break;
		case SDLK_2:
			InsertCharacter('2');
			break;
		case SDLK_3:
			InsertCharacter('3');
			break;
		case SDLK_4:
			InsertCharacter('4');
			break;
		case SDLK_5:
			InsertCharacter('5');
			break;
		case SDLK_6:
			InsertCharacter('6');
			break;
		case SDLK_7:
			InsertCharacter('7');
			break;
		case SDLK_8:
			InsertCharacter('8');
			break;
		case SDLK_9:
			InsertCharacter('9');
			break;
		case SDLK_LSHIFT:
			SetShift(true);
			break;
		case SDLK_RSHIFT:
			SetShift(true);
			break;
		case SDLK_LCTRL:
			SetCTRL(true);
			break;
		case SDLK_RCTRL:
			SetCTRL(true);
			break;
		}
	}
	else
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_d:
			return DELETE_CAPTIONS;
			break;
		case SDLK_e:
			currentime_ = ENGLISH;
			tempstring_ = "";
			return SET_TEXT_ENGLISH;
			break;
		case SDLK_j:
			currentime_ = JAPANESE;
			return SET_TEXT_JAPANESE;
			break;
		case SDLK_v:
			currenttext_ = currenttext_ + SDL_GetClipboardText();
			if (currenttexttexture_ != NULL)
				currenttexttexture_->CreateQuickTextureFromText(currenttext_ + '|');
			break;
		case SDLK_RETURN:
			return TEXT_FINALIZED;
			break;
		case SDLK_KP_ENTER:
			return TEXT_FINALIZED;
			break;
		}
	}

	return NO_MACRO;
}

char KeyboardEntry::KeyDownInputEnglish(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_SPACE:
		InsertCharacter(' ');
		break;
	case SDLK_BACKSPACE:
		DeleteCharacter();
		return 0;
	case SDLK_a:
		return 'a';
	case SDLK_b:
		return 'b';
	case SDLK_c:
		return 'c';
	case SDLK_d:
		return 'd';
	case SDLK_e:
		return 'e';
	case SDLK_f:
		return 'f';
	case SDLK_g:
		return 'g';
	case SDLK_h:
		return 'h';
	case SDLK_i:
		return 'i';
	case SDLK_j:
		return 'j';
	case SDLK_k:
		return 'k';
	case SDLK_l:
		return 'l';
	case SDLK_m:
		return 'm';
	case SDLK_n:
		return 'n';
	case SDLK_o:
		return 'o';
	case SDLK_p:
		return 'p';
	case SDLK_q:
		return 'q';
	case SDLK_r:
		return 'r';
	case SDLK_s:
		return 's';
	case SDLK_t:
		return 't';
	case SDLK_u:
		return 'u';
	case SDLK_v:
		return 'v';
	case SDLK_w:
		return 'w';
	case SDLK_x:
		return 'x';
	case SDLK_y:
		return 'y';
	case SDLK_z:
		return 'z';
	}

	return 0;
}

void KeyboardEntry::KeyDownInputJapaneseHiragana(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + hiraganamap_[nexttempchar_];
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ちゃ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"さ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"は";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ば";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"だ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"が";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"じゃ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"か";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"ま";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"ぱ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ら";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"た";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"わ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"や";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ざ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ん")
																			{
																				tempstring_ = tempstring_ + u8"な";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ひゃ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"きゃ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"みゃ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"りゃ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"んy")
																								{
																									tempstring_ = tempstring_ + u8"にゃ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ぎゃ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"びゃ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ぴゃ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"あ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_b:
		if (std::string("b").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "b";
			}
			else
			{
				if (nexttempchar_ == "b")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "b";
		}
		break;
	case SDLK_c:
		if (std::string("c").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "c";
			}
			else
			{
				if (nexttempchar_ == "c")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "c";
		}
		break;
	case SDLK_d:
		if (std::string("d").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "d";
			}
			else
			{
				if (nexttempchar_ == "d")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "d";
		}
		break;
	case SDLK_e:
		if ((std::string("s h b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "s")
			{
				tempstring_ = tempstring_ + u8"せ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"へ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"べ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"で";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"げ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"け";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"め";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ぺ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"れ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"て";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ゑ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"ぜ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ん")
															{
																tempstring_ = tempstring_ + u8"ね";
																nexttempchar_ = "";
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"え";
			nexttempchar_ = "";
		}
		break;
	case SDLK_f:
		if (std::string("f").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "f";
			}
			else
			{
				if (nexttempchar_ == "f")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "f";
		}
		break;
	case SDLK_g:
		if (std::string("g").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "g";
			}
			else
			{
				if (nexttempchar_ == "g")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "g";
		}
		break;
	case SDLK_h:
		if (std::string("csh").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "h";
			}
			else
			{
				if (nexttempchar_ == "s")
				{
					nexttempchar_ = "sh";
				}
				else
				{
					if (nexttempchar_ == "c")
					{
						nexttempchar_ = "ch";
					}
					else
					{
						if (nexttempchar_ == "h" && nexttempchar_ != "sh" && nexttempchar_ != "ch")
						{
							tempstring_ = tempstring_ + u8"っ";
						}
					}
				}
			}
		}
		break;
	case SDLK_i:
		if ((std::string("sh ch b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"し";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"ひ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"び";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"ぢ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"ぎ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"き";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"み";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ぴ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"り";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"ち";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ゐ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"じ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ん")
															{
																tempstring_ = tempstring_ + u8"に";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "ch")
																{
																	tempstring_ = tempstring_ + u8"ち";
																	nexttempchar_ = "";
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"い";
			nexttempchar_ = "";
		}
		break;
	case SDLK_j:
		if (std::string("j").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "j";
			}
			else
			{
				if (nexttempchar_ == "j")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "j";
		}
		break;
	case SDLK_k:
		if (std::string("k").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "k";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "k";
		}
		break;
	case SDLK_m:
		if (std::string("m").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "m";
			}
			else
			{
				if (nexttempchar_ == "m")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "m";
		}
		break;
	case SDLK_n:
		if (std::string(u8"ん").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = u8"ん";
			}
			else
			{
				if (nexttempchar_ == u8"ん")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = u8"ん";
		}
		break;
	case SDLK_o:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"しょ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ちょ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"そ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ほ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ぼ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ど";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ご";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"じょ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"こ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"も";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"ぽ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ろ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"と";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"を";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"よ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ぞ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ん")
																			{
																				tempstring_ = tempstring_ + u8"の";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ひょ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"きょ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"みょ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"りょ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"んy")
																								{
																									tempstring_ = tempstring_ + u8"にょ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ぎょ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"びょ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ぴょ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"お";
			nexttempchar_ = "";
		}
		break;
	case SDLK_p:
		if (std::string("p").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "p";
			}
			else
			{
				if (nexttempchar_ == "p")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "p";
		}
		break;
	case SDLK_r:
		if (std::string("r").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "r";
			}
			else
			{
				if (nexttempchar_ == "r")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "r";
		}
		break;
	case SDLK_s:
		if (std::string("ts").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "s";
			}
			else
			{
				if (nexttempchar_ == "s" && nexttempchar_ != "ts")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
				else
				{
					if (nexttempchar_ == "t")
					{
						nexttempchar_ = "ts";
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "s";
		}
		break;
	case SDLK_t:
		if (std::string("t").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "t";
			}
			else
			{
				if (nexttempchar_ == "t")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "t";
		}
		break;
	case SDLK_u:
		if ((std::string("sh ch hy by d gy j ky my py ry ts w z f").find(nexttempchar_) != std::string::npos || std::string(u8"んy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"しゅ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"ちゅ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"す";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "f")
						{
							tempstring_ = tempstring_ + u8"ふ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ぶ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"づ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ぐ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"じゅ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"く";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"む";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"ぷ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"る";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "ts")
															{
																tempstring_ = tempstring_ + u8"つ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "y")
																{
																	tempstring_ = tempstring_ + u8"ゆ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "z")
																	{
																		tempstring_ = tempstring_ + u8"ず";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == u8"ん")
																		{
																			tempstring_ = tempstring_ + u8"ぬ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == "hy")
																			{
																				tempstring_ = tempstring_ + u8"ひゅ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "ky")
																				{
																					tempstring_ = tempstring_ + u8"きゅ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "my")
																					{
																						tempstring_ = tempstring_ + u8"みゅ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "ry")
																						{
																							tempstring_ = tempstring_ + u8"りゅ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == u8"んy")
																							{
																								tempstring_ = tempstring_ + u8"にゅ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == "gy")
																								{
																									tempstring_ = tempstring_ + u8"ぎゅ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "by")
																									{
																										tempstring_ = tempstring_ + u8"びゅ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "py")
																										{
																											tempstring_ = tempstring_ + u8"ぴゅ";
																											nexttempchar_ = "";
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"う";
			nexttempchar_ = "";
		}
		break;
	case SDLK_w:
		if (std::string("w").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "w";
			}
			else
			{
				if (nexttempchar_ == "w")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "w";
		}
		break;
	case SDLK_y:
		if (std::string("k h m r g b p").find(nexttempchar_) != std::string::npos || std::string(u8"ん").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "y";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					nexttempchar_ = "ky";
				}
				else
				{
					if (nexttempchar_ == u8"ん")
					{
						nexttempchar_ = u8"んy";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							nexttempchar_ = "hy";
						}
						else
						{
							if (nexttempchar_ == "m")
							{
								nexttempchar_ = "my";
							}
							else
							{
								if (nexttempchar_ == "m")
								{
									nexttempchar_ = "my";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										nexttempchar_ = "gy";
									}
									else
									{
										if (nexttempchar_ == "b")
										{
											nexttempchar_ = "by";
										}
										else
										{
											if (nexttempchar_ == "p")
											{
												nexttempchar_ = "py";
											}
											else
											{
												if (nexttempchar_ == "r")
												{
													nexttempchar_ = "ry";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "y";
		}
		break;
	case SDLK_z:
		if (std::string("z").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "z";
			}
			else
			{
				if (nexttempchar_ == "z")
				{
					tempstring_ = tempstring_ + u8"っ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "z";
		}
		break;
	case SDLK_MINUS:
		tempstring_ = tempstring_ + nexttempchar_ + u8"ー";
		nexttempchar_ = "";
		break;
	case SDLK_BACKSPACE:
		if (nexttempchar_ != "")
		{
				nexttempchar_.pop_back();
		}
		else
		{
			if (tempstring_ != "")
			{
				tempstring_.pop_back();
			}
			else
			{
				DeleteCharacter();
			}
		}
		break;
	case SDLK_RETURN:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_KP_ENTER:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	}
}

void KeyboardEntry::KeyDownInputJapaneseKatakana(const SDL_Event & e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_a:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シャ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チャ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"サ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ハ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"バ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ダ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ガ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジャ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"カ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"マ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"パ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ラ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"タ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"ワ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"ヤ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ザ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ン")
																			{
																				tempstring_ = tempstring_ + u8"ナ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ヒャ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"キャ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"ミャ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"リャ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ンy")
																								{
																									tempstring_ = tempstring_ + u8"ニャ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ギャ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"ビャ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ピャ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"ア";
			nexttempchar_ = "";
		}
		break;
	case SDLK_b:
		if (std::string("b").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "b";
			}
			else
			{
				if (nexttempchar_ == "b")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "b";
		}
		break;
	case SDLK_c:
		if (std::string("c").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "c";
			}
			else
			{
				if (nexttempchar_ == "c")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "c";
		}
		break;
	case SDLK_d:
		if (std::string("d").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "d";
			}
			else
			{
				if (nexttempchar_ == "d")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "d";
		}
		break;
	case SDLK_e:
		if ((std::string("s h b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "s")
			{
				tempstring_ = tempstring_ + u8"セ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"ヘ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"ベ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"デ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"ゲ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"ケ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"メ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ペ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"レ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"テ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ヱ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"ゼ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ン")
															{
																tempstring_ = tempstring_ + u8"ネ";
																nexttempchar_ = "";
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"エ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_f:
		if (std::string("f").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "f";
			}
			else
			{
				if (nexttempchar_ == "f")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "f";
		}
		break;
	case SDLK_g:
		if (std::string("g").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "g";
			}
			else
			{
				if (nexttempchar_ == "g")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "g";
		}
		break;
	case SDLK_h:
		if (std::string("csh").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "h";
			}
			else
			{
				if (nexttempchar_ == "s")
				{
					nexttempchar_ = "sh";
				}
				else
				{
					if (nexttempchar_ == "c")
					{
						nexttempchar_ = "ch";
					}
					else
					{
						if (nexttempchar_ == "h" && nexttempchar_ != "sh" && nexttempchar_ != "ch")
						{
							tempstring_ = tempstring_ + u8"ッ";
						}
					}
				}
			}
		}
		break;
	case SDLK_i:
		if ((std::string("sh ch b d g j k m p r t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "h")
				{
					tempstring_ = tempstring_ + u8"ヒ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "b")
					{
						tempstring_ = tempstring_ + u8"ビ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "d")
						{
							tempstring_ = tempstring_ + u8"ヂ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "g")
							{
								tempstring_ = tempstring_ + u8"ギ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "k")
								{
									tempstring_ = tempstring_ + u8"キ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "m")
									{
										tempstring_ = tempstring_ + u8"ミ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "p")
										{
											tempstring_ = tempstring_ + u8"ピ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "r")
											{
												tempstring_ = tempstring_ + u8"リ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "t")
												{
													tempstring_ = tempstring_ + u8"チ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "w")
													{
														tempstring_ = tempstring_ + u8"ヰ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "z")
														{
															tempstring_ = tempstring_ + u8"ジ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == u8"ン")
															{
																tempstring_ = tempstring_ + u8"ニ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "ch")
																{
																	tempstring_ = tempstring_ + u8"チ";
																	nexttempchar_ = "";
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"イ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_j:
		if (std::string("j").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "j";
			}
			else
			{
				if (nexttempchar_ == "j")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "j";
		}
		break;
	case SDLK_k:
		if (std::string("k").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "k";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "k";
		}
		break;
	case SDLK_m:
		if (std::string("m").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "m";
			}
			else
			{
				if (nexttempchar_ == "m")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "m";
		}
		break;
	case SDLK_n:
		if (std::string(u8"ン").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = u8"ン";
			}
			else
			{
				if (nexttempchar_ == u8"ン")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = u8"ン";
		}
		break;
	case SDLK_o:
		if ((std::string("sh ch hy by d gy j ky my py ry t w z").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"ショ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チョ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"ソ";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							tempstring_ = tempstring_ + u8"ホ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ボ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ド";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"ゴ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジョ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"コ";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"モ";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"ポ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ロ";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "t")
															{
																tempstring_ = tempstring_ + u8"ト";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "w")
																{
																	tempstring_ = tempstring_ + u8"ヲ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "y")
																	{
																		tempstring_ = tempstring_ + u8"ヨ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == "z")
																		{
																			tempstring_ = tempstring_ + u8"ゾ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == u8"ン")
																			{
																				tempstring_ = tempstring_ + u8"ノ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "hy")
																				{
																					tempstring_ = tempstring_ + u8"ヒョ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "ky")
																					{
																						tempstring_ = tempstring_ + u8"キョ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "my")
																						{
																							tempstring_ = tempstring_ + u8"ミョ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == "ry")
																							{
																								tempstring_ = tempstring_ + u8"リョ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == u8"ンy")
																								{
																									tempstring_ = tempstring_ + u8"ニョ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "gy")
																									{
																										tempstring_ = tempstring_ + u8"ギョ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "by")
																										{
																											tempstring_ = tempstring_ + u8"ビョ";
																											nexttempchar_ = "";
																										}
																										else
																										{
																											if (nexttempchar_ == "py")
																											{
																												tempstring_ = tempstring_ + u8"ピョ";
																												nexttempchar_ = "";
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"オ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_p:
		if (std::string("p").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "p";
			}
			else
			{
				if (nexttempchar_ == "p")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "p";
		}
		break;
	case SDLK_r:
		if (std::string("r").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "r";
			}
			else
			{
				if (nexttempchar_ == "r")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "r";
		}
		break;
	case SDLK_s:
		if (std::string("ts").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "s";
			}
			else
			{
				if (nexttempchar_ == "s" && nexttempchar_ != "ts")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
				else
				{
					if (nexttempchar_ == "t")
					{
						nexttempchar_ = "ts";
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "s";
		}
		break;
	case SDLK_t:
		if (std::string("t").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "t";
			}
			else
			{
				if (nexttempchar_ == "t")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "t";
		}
		break;
	case SDLK_u:
		if ((std::string("sh ch hy by d gy j ky my py ry ts w z f").find(nexttempchar_) != std::string::npos || std::string(u8"ンy").find(nexttempchar_) != std::string::npos) && nexttempchar_ != "")
		{
			if (nexttempchar_ == "sh")
			{
				tempstring_ = tempstring_ + u8"シュ";
				nexttempchar_ = "";
			}
			else
			{
				if (nexttempchar_ == "ch")
				{
					tempstring_ = tempstring_ + u8"チュ";
					nexttempchar_ = "";
				}
				else
				{
					if (nexttempchar_ == "s")
					{
						tempstring_ = tempstring_ + u8"ス";
						nexttempchar_ = "";
					}
					else
					{
						if (nexttempchar_ == "f")
						{
							tempstring_ = tempstring_ + u8"フ";
							nexttempchar_ = "";
						}
						else
						{
							if (nexttempchar_ == "b")
							{
								tempstring_ = tempstring_ + u8"ブ";
								nexttempchar_ = "";
							}
							else
							{
								if (nexttempchar_ == "d")
								{
									tempstring_ = tempstring_ + u8"ヅ";
									nexttempchar_ = "";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										tempstring_ = tempstring_ + u8"グ";
										nexttempchar_ = "";
									}
									else
									{
										if (nexttempchar_ == "j")
										{
											tempstring_ = tempstring_ + u8"ジュ";
											nexttempchar_ = "";
										}
										else
										{
											if (nexttempchar_ == "k")
											{
												tempstring_ = tempstring_ + u8"ク";
												nexttempchar_ = "";
											}
											else
											{
												if (nexttempchar_ == "m")
												{
													tempstring_ = tempstring_ + u8"ム";
													nexttempchar_ = "";
												}
												else
												{
													if (nexttempchar_ == "p")
													{
														tempstring_ = tempstring_ + u8"プ";
														nexttempchar_ = "";
													}
													else
													{
														if (nexttempchar_ == "r")
														{
															tempstring_ = tempstring_ + u8"ル";
															nexttempchar_ = "";
														}
														else
														{
															if (nexttempchar_ == "ts")
															{
																tempstring_ = tempstring_ + u8"ツ";
																nexttempchar_ = "";
															}
															else
															{
																if (nexttempchar_ == "y")
																{
																	tempstring_ = tempstring_ + u8"ユ";
																	nexttempchar_ = "";
																}
																else
																{
																	if (nexttempchar_ == "z")
																	{
																		tempstring_ = tempstring_ + u8"ズ";
																		nexttempchar_ = "";
																	}
																	else
																	{
																		if (nexttempchar_ == u8"ン")
																		{
																			tempstring_ = tempstring_ + u8"ヌ";
																			nexttempchar_ = "";
																		}
																		else
																		{
																			if (nexttempchar_ == "hy")
																			{
																				tempstring_ = tempstring_ + u8"ヒュ";
																				nexttempchar_ = "";
																			}
																			else
																			{
																				if (nexttempchar_ == "ky")
																				{
																					tempstring_ = tempstring_ + u8"キュ";
																					nexttempchar_ = "";
																				}
																				else
																				{
																					if (nexttempchar_ == "my")
																					{
																						tempstring_ = tempstring_ + u8"ミュ";
																						nexttempchar_ = "";
																					}
																					else
																					{
																						if (nexttempchar_ == "ry")
																						{
																							tempstring_ = tempstring_ + u8"リュ";
																							nexttempchar_ = "";
																						}
																						else
																						{
																							if (nexttempchar_ == u8"ンy")
																							{
																								tempstring_ = tempstring_ + u8"ニュ";
																								nexttempchar_ = "";
																							}
																							else
																							{
																								if (nexttempchar_ == "gy")
																								{
																									tempstring_ = tempstring_ + u8"ギュ";
																									nexttempchar_ = "";
																								}
																								else
																								{
																									if (nexttempchar_ == "by")
																									{
																										tempstring_ = tempstring_ + u8"ビュ";
																										nexttempchar_ = "";
																									}
																									else
																									{
																										if (nexttempchar_ == "py")
																										{
																											tempstring_ = tempstring_ + u8"ピュ";
																											nexttempchar_ = "";
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_ + u8"ウ";
			nexttempchar_ = "";
		}
		break;
	case SDLK_w:
		if (std::string("w").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "w";
			}
			else
			{
				if (nexttempchar_ == "w")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "w";
		}
		break;
	case SDLK_y:
		if (std::string("k h m r g b p").find(nexttempchar_) != std::string::npos || std::string(u8"ン").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "y";
			}
			else
			{
				if (nexttempchar_ == "k")
				{
					nexttempchar_ = "ky";
				}
				else
				{
					if (nexttempchar_ == u8"ン")
					{
						nexttempchar_ = u8"ンy";
					}
					else
					{
						if (nexttempchar_ == "h")
						{
							nexttempchar_ = "hy";
						}
						else
						{
							if (nexttempchar_ == "m")
							{
								nexttempchar_ = "my";
							}
							else
							{
								if (nexttempchar_ == "m")
								{
									nexttempchar_ = "my";
								}
								else
								{
									if (nexttempchar_ == "g")
									{
										nexttempchar_ = "gy";
									}
									else
									{
										if (nexttempchar_ == "b")
										{
											nexttempchar_ = "by";
										}
										else
										{
											if (nexttempchar_ == "p")
											{
												nexttempchar_ = "py";
											}
											else
											{
												if (nexttempchar_ == "r")
												{
													nexttempchar_ = "ry";
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "y";
		}
		break;
	case SDLK_z:
		if (std::string("z").find(nexttempchar_) != std::string::npos || nexttempchar_ == "")
		{
			if (nexttempchar_ == "")
			{
				nexttempchar_ = "z";
			}
			else
			{
				if (nexttempchar_ == "z")
				{
					tempstring_ = tempstring_ + u8"ッ";
				}
			}
		}
		else
		{
			tempstring_ = tempstring_ + nexttempchar_;
			nexttempchar_ = "z";
		}
		break;
	case SDLK_MINUS:
		tempstring_ = tempstring_ + nexttempchar_ + u8"ー";
		nexttempchar_ = "";
		break;
	case SDLK_BACKSPACE:
		if (nexttempchar_ != "")
		{
			nexttempchar_.pop_back();
		}
		else
		{
			if (tempstring_ != "")
			{
				tempstring_.pop_back();
			}
			else
			{
				DeleteCharacter();
			}
		}
		break;
	case SDLK_RETURN:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	case SDLK_KP_ENTER:
		InsertString(tempstring_ + nexttempchar_);
		tempstring_ = "";
		nexttempchar_ = "";
		break;
	}
}

void KeyboardEntry::KeyUpInput(const SDL_Event &e)
{
	switch (e.key.keysym.sym)
	{
	case SDLK_LSHIFT:
		SetShift(false);
		break;
	case SDLK_RSHIFT:
		SetShift(false);
		break;
	case SDLK_LCTRL:
		SetCTRL(false);
		break;
	case SDLK_RCTRL:
		SetCTRL(false);
		break;
	}
}

TextInput *KeyboardEntry::GetTexture()
{
	return currenttexttexture_;
}
