<html>
<head>
<meta http-equiv='Content-Type' content='text/html; charset=big5'>
<title>Web base�i�P�s�޲z�t��</title>
</head>
<body>
<?php 
    // -------------���X�Ҧ����ʥD��ƪ���---------------
	include("mysqlcntdb.php");
	$SQLStr = "SELECT * FROM  purchmst";
	$res = mysql_query($SQLStr);
	
    //--------------�p���`���Ƥέ���------------------
	$total=mysql_num_rows($res);
	$lista=ceil($total/10);
?>
<!----�ǵ�ppurchmst_inq2.php,����j�M---------->
<form name="form1" method="post" action="purchase/purchmst_inq2.php?purcmtranno=' . $purcmtranno . '">
  <table width="782" border="1" align="center" cellspacing="0" cellpadding="0" >
    <tr bgcolor="#99CCFF"> 
      <td align="center">
<?php
    //--------------���ƿ�ܧe�{�γs��---------------
     echo "�j�M���ʥD��ƪ����&nbsp;&nbsp; ��&nbsp";
	for($i = 1;$i<=$lista;$i++) 
	{
		echo "  <a href=index.php?Select=266&page=$i>$i</a>|";
	}
       echo "��, �@".$total."��&nbsp;&nbsp";
?> 
    </td>
    </tr>
  </table>
  <table width="782" border="0" align="center" cellpadding="0" cellspacing="0" >
    <tr> 
      <td> 
        <table width="782" border="1" align="center" bgcolor="#FFFFFF">
          <tr>                     
            <td bgcolor="#99CCFF" align="center"> 
             ���ʳ渹
            </td>
            <td bgcolor="#99CCFF" align="center"> 
             �����t��
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              ��f���
            </td>
            <td bgcolor="#99CCFF" align="center"> 
              �������O
            </td>             
          </tr>		  
<?php
      //--------------��ܭ��Ʊ��ʥD��Ƨe�{�γs�������\��-----------
	  $page=$_GET["page"];
	  if(empty($page)) $page=1;
	  $first=10*($page - 1);
	  $SQLStr="select * from purchmst order by purcmtranno limit $first , 10";
	  $res = mysql_query($SQLStr);
	 
       while (list($purcmtranno, $purcmvend,  $purcmdate, $purcmtype)=mysql_fetch_row($res))
		{
        // ������ʥD��ƪ���ƨçe�{
            echo "<tr border='0'   bgcolor='#ffffff'>";			
			echo "<td align='center'><a href='purchase/purchmst_inq2.php?purcmtranno=" . $purcmtranno . "'>" . $purcmtranno . "</a></td>\n";
			echo "<td align='center'>" . $purcmvend  . "</td>\n";
			echo "<td align='center'>";
			   if ($purcmdate == '') 
			      $purcmdate="�L���";	        
			      echo  $purcmdate . "</td>\n";
            echo "<td align='center'>";			  
			   if ($purcmtype == '') 
			      $purcmtype="�ӺD��";	        
			      echo  $purcmtype . "</td>\n";		

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
