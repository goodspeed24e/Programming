<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php
// -------------���X�Ҧ��t�Ӫ����---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM vend";
	$res = mysql_query($SQLStr);	
//--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!---�ǥX�j�M����,����vendsupamt_inq2.php----->
<form name="form1" method="post" action="vend/vendsupamt_inq2.php?vendno='.$vendno.'">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr> 
      <td align="center" bgcolor="#99CCFF">
<?php
//--------------���ƿ�ܧe�{�γs��---------------
     echo "�j�M���I�b�ڸ��&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=226&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?>
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr > 
      <td> 
        <table width="782" border="1" align="center"  bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
              �t�ӧǸ�
            </td>
            <td bgcolor="#99CCFF" align="center"> 
            �t�ӦW��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �Τ@�s��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ���q�a�}
            </td>             
          </tr>
<?php
//--------------��ܭ��Ƽt�Ӹ�Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
//-------------�j�M���e,�t�ӱb�ڸ��-------------------------------------------------- 		  
	  $SQLStr="select * from vend order by vendno  limit $first , 10";
	  $res = mysql_query($SQLStr);	 
      while (list($vendno, $vendname,  $vendsname,  $vendleader,  $vendinvoice,  $vendcontact,  $vendtel,  $vendmobil,  $vendfax,  $vendtype,  $vendsales,  $vendadr,  $vendpradr,  $vendinadr,  $vendemail,  $vendhttp,  $venddate,  $vendclosdate,  $vendprictype,  $vendpricper,  $vendprepamt,  $vendapamt,  $vendchkamt,  $vendprepdc,  $vendapdc,  $vendchkdc)=mysql_fetch_row($res))
		{
//------------��Ʒj�M���e�e�{,�t�ӱb�ڸ�Ʃ���--------------------------------------------	
			echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'>" .$vendno. "</td>\n";
			echo "<td align='center'><a href='vend/vendsupamt_inq2.php?vendno=".$vendno."'>" .$vendname. "</a></td>\n";
			echo "<td align='center'>" . $vendinvoice. "</td>\n";
			echo "<td align='center'>" . $vendadr. "</td>\n";	
			echo "</tr>";
		}	
?>         
        </table>
      </td>
    </tr>
  </table>    
</form>
</body>
</html>
