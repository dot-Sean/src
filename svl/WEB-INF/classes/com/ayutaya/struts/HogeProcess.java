package com.ayutaya.struts;

import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.struts.action.*;

public final class HogeProcess extends Action {
  // ビジネスロジックがここに
  public ActionForward execute (
    ActionMapping map,
    ActionForm frm,
    HttpServletRequest request,
    HttpServletResponse response ) {
    HogeForm objFrm = (HogeForm) frm;
      request.setAttribute("objFrm", objFrm);
      return (map.findForward("success"));
  }
}
