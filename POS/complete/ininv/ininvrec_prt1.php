<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=big5">
<title>�i�f����ï</title>
<style type="text/css">
<!--
.style1 {font-size: 18px}
-->
</style>
</head>

<body >
<!------ �ǵ� ininvrec_prt2.php �ɮ�  ------>
<form name='form1' method='post' action='ininv/ininvrec_prt2.php?tranprodno1=" . $row[tranprodno1] . "&tranprodno2=" . $row[tranprodno2] . "'>
<table width="259" height="150" border="1" bgcolor="#FFFFFF" align="center" cellpadding="0" cellspacing="0">
  <tr >
    <td width="100%"  valign="middle">	  <table width="100%"   border="0" cellpadding="0" cellspacing="0">
       <tr  bgcolor="#99FFCC">
        <td width="100%" height="58" align="center" valign="middle">
		�i�f����ï
		</td>
       </tr>
    </table></td>
  </tr>
  <tr >
    <td  >	  <table  border="0"  cellpadding="0" cellspacing="0">
      <tr    align="center" bgcolor="#EBEBEB" >
        <td width="255" height="133" align="center" >
		<br>
		���~�s��<br>		<p>
		<!--�]�w�C�L�j�M��ư϶�,��J�i�f���------>	
            <input type="text" name="tranprodno1" size="10" value="<?=$row['tranprodno1']?>">            
��
            <input type="text" name="tranprodno2" size="10" value="<?=$row['tranprodno2']?>">
        </p>
          <p>
            <input type="submit" name="Submit" value="�C�L" >
          </p>
          <p >&nbsp;          </p></td>
      </tr>
    </table></td>
  </tr>
</table>
</form>
</body>
</html>
